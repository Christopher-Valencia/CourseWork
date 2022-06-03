/*
Christopher Valencia
COMP 429 Fall 2021
Project 02
*/

package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"net"
	"os"
	"strconv"
	"time"
)

func main() {
	//Start listener
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		// handle error
		fmt.Println("Error: listen problem")
	}
	defer listener.Close()

	for {
		//accept tcp message
		conn, err := listener.Accept()
		if err != nil {
			// handle error
			fmt.Println("Error: listen accept problem")
		}
		//parse and fulfill requests
		go handleRequest(conn)
	}
}

func handleRequest(conn net.Conn) {
	buf := make([]byte, 512)
	//read from connection into buffer
	_, err := conn.Read(buf)
	if err != nil {
		// handle error
		fmt.Println("Error: conn read problem")
		return
	}
	//fmt.Println("Message received\nSize: ", n, "\nBytes: ", buf)

	//check for the method being used GET or HEAD otherwise 404
	if string(buf[:bytes.IndexByte(buf, byte(' '))]) == "GET" {
		f := buf[bytes.IndexByte(buf, byte(' '))+1:]
		f = f[:bytes.IndexByte(f, byte(' '))]
		path := []byte("www")
		path = append(path, f...)

		//Get file stats
		fInfo, err := os.Stat(string(path))
		if err != nil {
			fmt.Println("ERROR: in GET stat problem")
			send404(conn)
			return
		}

		//Read the file designated by the path
		fileData, err := ioutil.ReadFile(string(path))
		if err != nil {
			fmt.Println("ERROR: read problem")
			send404(conn)
			return
		}
		//create GET response message
		mess := "HTTP/1.1 200 OK\r\nServer: cihttpd\r\nContent-Length: "
		mess += strconv.Itoa(len(fileData))
		mess += "\r\nLast-Modified: "
		mess += fInfo.ModTime().Format(time.RFC1123)
		mess += "\r\n\r\n"
		message := append([]byte(mess), fileData...)
		conn.Write(message)
		fmt.Println("Response sent:\n", mess)

	} else if string(buf[:bytes.IndexByte(buf, byte(' '))]) == "HEAD" {
		//parse the path from the message
		f := buf[bytes.IndexByte(buf, byte(' '))+1:]
		f = f[:bytes.IndexByte(f, byte(' '))]
		path := []byte("www")
		path = append(path, f...)

		//get file statistics
		fInfo, err := os.Stat(string(path))
		if err != nil {
			fmt.Println("ERROR: in HEAD stat problem")
			send404(conn)
			return
		}

		//create HEAD response message
		mess := "HTTP/1.1 200 OK\r\nServer: cihttpd\r\nContent-Length: "
		mess += strconv.Itoa(int(fInfo.Size()))
		mess += "\r\nLast-Modified: "
		mess += fInfo.ModTime().Format(time.RFC1123)
		mess += "\r\n\r\n"
		//fmt.Println(mess)
		conn.Write([]byte(mess))
		fmt.Println("Response sent")

	} else {
		send404(conn)
	}
	//conn.Close()
}

func send404(conn net.Conn) {
	//Send 404 page
	fileData, err := ioutil.ReadFile("www/404.html")
	if err != nil {
		fmt.Println("ERROR: 404 read problem")
	}

	//create 404 response message
	mess := "HTTP/1.1 404 Not Found\r\nServer: cihttpd\r\nContent-Length: "
	mess += strconv.Itoa(len(fileData))
	mess += "\r\n\r\n"
	message := append([]byte(mess), fileData...)
	//fmt.Println(mess)
	conn.Write(message)
	fmt.Println("Response sent")
}
