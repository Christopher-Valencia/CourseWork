/*Christopher Valencia
COMP 429 Fall 2021
Project 01
*/
package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func main() {
	// Where we want to send our traffic
	dst, err := net.ResolveUDPAddr("udp", "127.0.0.1:9001")
	if err != nil {
		log.Fatal(err)
	}

	// Prepare the socket
	conn, err := net.DialUDP("udp", nil, dst)
	if err != nil {
		log.Fatal(err)
	}
	// Close the socket when the function exists
	defer conn.Close()

	// Write "some data\n" to the socket
	// fmt.Fprintf(conn, "some data\n")
	// fmt.Println("Sent some data")

	reader := bufio.NewReader(os.Stdin)
	text, _ := reader.ReadString('\n')
	// convert CRLF to LF
	text = strings.Replace(text, "\n", "", -1)
	fmt.Fprintf(conn, text)
	fmt.Printf("Sent %s", text)

	if text[0:2] == "01" {
		// Read the incoming bytes
		data := make([]byte, 1500)
		var message []byte
		for {
			size, _, err := conn.ReadFrom(data)
			if err != nil {
				log.Print("Error: " + err.Error())
			}

			fmt.Printf("Read %v bytes.\n", size)
			if size <= 4 {
				break
			}
			message = append(message, data[4:size]...)

			if (len(data) - 4) < 512 {
				break
			}
		}
		fmt.Println("Complete Message is:")

		_, loc := getModeLoc(text)
		filename := string(text[2 : loc-1])
		path := append([]byte("files/"), []byte(filename)...)
		f, err := os.Create(string(path))
		if err != nil {
			log.Fatal(err)
		}
		defer f.Close()

		_, err2 := f.WriteString(string(message))
		if err2 != nil {
			log.Fatal(err2)
		}

		fmt.Println("done")
		fmt.Println("Client Done!!!")
		return
	}
	if text[0:2] == "02" {
		fmt.Println("Sending Write Request")
		_, loc := getModeLoc(text)
		filename := string(text[2 : loc-1])
		path := append([]byte("files/"), []byte(filename)...)
		fmt.Println(string(path))
		f, err := os.Open(string(path))
		if err != nil {
			fmt.Println("ERROR: in readFile func opening problem")
			log.Fatal(err)
		}

		//2 bytes opcode | 2 bytes block # | data
		chunks := make([]byte, 512)
		blockNum := 1
		for {
			n, readErr := f.Read(chunks)
			message := []byte("03")
			var num []byte
			if blockNum > 15 {
				num = []byte(string(blockNum))
			} else {
				num = []byte(string(byte(0)))
				num = append(num, []byte(string(blockNum))...)
				fmt.Println(blockNum)
			}
			message = append(message, num...)
			message = append(message, chunks[:n]...)

			//size := len(message)
			fmt.Fprintf(conn, string(message))
			if err != nil {
				log.Fatal(err)
			}

			if readErr == io.EOF {
				break
			}
			blockNum++
		}
		fmt.Println("File sent")
	}
}

func getModeLoc(data string) (int, int) {
	newData := strings.ToLower(data)
	loc := strings.Index(newData, "netascii")
	if loc != -1 {
		return 1, loc
	}
	loc = strings.Index(newData, "octet")
	if loc != -1 {
		return 2, loc
	}
	loc = strings.Index(newData, "mail")
	if loc != -1 {
		return 3, loc
	}
	return 0, loc
}
