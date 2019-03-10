# Lab 2.5 - Depth-limiting Web Crawler

## Description

Web crawler in Go with depth limitation.

## Instructions

To run it type the following command `go run crawl3.go -depth=n website` where n is an integer value which limits the depth of the crawler and website is the url to start crawling from.

```
go run crawl3.go -depth=2 https://google.com/
go run crawl3.go -depth=3 http://www.gopl.io/
go run crawl3.go -depth=1 http://www.gopl.io/
```

The commands above are examples of how you will run the program.
