// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"flag"
)

var usersList = make([]string, 0)

//!+broadcaster
type client chan <- string // an outgoing message channel

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)

func deleteUser(userName string){
	for i, user := range usersList {
		if userName == user {
			usersList[i] = usersList[len(usersList) - 1]
			usersList[len(usersList) - 1] = ""
			usersList = usersList[:len(usersList) - 1]
		}
	}
}

func getUserList(ch chan string) {
	for _, user := range usersList {
		if user != "" {
			ch <- user
		}
	}
}

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <- messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				cli <- msg
			}


		case cli := <- entering:
			clients[cli] = true

		case cli := <- leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

func isUserInList(username string) bool {
	for _, user := range usersList {
		if user == username {
			return true
		}
	}
	return false
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	//clients := make(map[client]bool) // all connected clients
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)
	
	who := ""//conn.RemoteAddr().String()

	usersList = append(usersList, "")

	input := bufio.NewScanner(conn)
	for input.Scan() {
		if usersList[len(usersList) - 1] == "" {
			if !isUserInList(input.Text()) {
				usersList[len(usersList) - 1] = input.Text()
				who = input.Text()
				ch <- "You are " + who
				messages <- who + " has arrived"
				entering <- ch
			} else {
				ch <- "Username is already in use, please enter another name:"
			}


		} else if input.Text() == "/users" {
			getUserList(ch)
		} else {
			messages <- who + ": " + input.Text()
		}	
	}
	// NOTE: ignoring potential errors from input.Err()

	leaving <- ch
	messages <- who + " has left"
	deleteUser(who)
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
func main() {

	//Handle flags
	hostPtr := flag.String("host", "localhost:8000", "a string")
	portPtr := flag.String("port", "9000", "a string")

	flag.Parse()

	fmt.Println("host:", *hostPtr)
	fmt.Println("port:", *portPtr)
	//End handling flags


	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main