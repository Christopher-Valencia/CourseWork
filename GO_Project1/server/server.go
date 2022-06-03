/*Christopher Valencia
COMP 429 Fall 2021
Project 01
*/
package main

import (
	"bytes"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func main() {
	conn, err := net.ListenPacket("udp", ":9001")
	if err != nil {
		log.Fatal(err)
	}

	for {
		data := make([]byte, 1500)

		size, addr, err := conn.ReadFrom(data)
		if err != nil {
			log.Fatal(err)
		}

		fmt.Printf("Read %v bytes.\n", size)
		fmt.Printf("Data: %s\n", data[:size])

		//for read or write
		//opcode 2 bytes | filename | 1 byte '0' | mode contains "netascii", "octet", or "mail" | 1 byte '0'
		opcode := data[0:2]
		switch {
		case bytes.Contains(opcode, []byte("01")):
			fmt.Println("Read Request Received")
			_, loc := getModeLoc(string(data))
			filename := string(data[2 : loc-1])
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

				size := len(message)
				size, err = conn.WriteTo(message[:size], addr)
				if err != nil {
					log.Fatal(err)
				}

				if readErr == io.EOF {
					break
				}
				blockNum++
			}
			fmt.Println("File sent")

		case bytes.Contains(opcode, []byte("02")):
			fmt.Println("Write Request Received")
			_, loc := getModeLoc(string(data))
			filename := string(data[2 : loc-1])

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

			fmt.Println("File Saved!!!")

		default:
			fmt.Println("Error: Bad OpCode!!!")
			break
		}

		size, err = conn.WriteTo(data[:size], addr)
		if err != nil {
			log.Print("Error: " + err.Error())
		}
		fmt.Printf("Sent %v bytes.\n", size)
	}

	// f, err := os.Open("Files/test.txt")
	// if err != nil {
	// 	log.Fatal(err)
	// }

	// chunks := make([]byte, 512)
	// for {
	// 	n, err := f.Read(chunks)
	// 	fmt.Println(chunks[:n])

	// 	if err == io.EOF {
	// 		break
	// 	}
	// }
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
