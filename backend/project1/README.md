# Accessing public HTTP APIs

💡 [Tap here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to leave your feedback on the project**. It's anonymous and will help our team make your educational experience better. We recommend completing the survey immediately after the project.

## Contents

[[_TOC_]]


## Chapter I 

### Introduction

In this project, you will form a number of request collections in Postman to retrieve data from public APIs without and with authorization. You'll learn the concepts of the HTTP protocol, its methods, and the data formats it operates with. You'll also look at the developer tools in Google Chrome.


## Chapter II

### What is API and what does it do?

The API (Application Programming Interface) is the contract that the program provides. "You can address me this way and that way, I undertake to do this and that."

In other words, an API is a set of functions that a program provides, with each function describing the format of the input data and the format in which it will be received. We'll talk more about API specifications later.

Using the API we can access data from a system developed by a company or a developer.

There are two types of APIs:
* Public — interfaces that are open to anyone and can be accessed by anyone to use them.
* Private — interfaces that are only accessible to internal developers or to developers from other teams/companies based on the granting of access rights to the interface. 
 
### HTTP 1.1

Read the official specification of this version of the protocol [here](https://httpwg.org/specs/rfc9112.html).

HTTP (HyperText Transfer Protocol) is an application layer protocol implemented on top of TCP/IP (prior to version 3.0, drafts of which already work on top of UDP). HTTP defines how the client and server interact and how content is requested and transferred over the Internet.

Currently, the HTTP protocol is (for the most part) what makes the World Wide Web work.

The API of many software products also implies the use of HTTP for data transfer. The data itself can be in any format, such as XML or JSON.

Typically, data transfers using the HTTP protocol are made over TCP/IP connections. The server software usually uses TCP port 80 (and if the port is not explicitly specified, the client software usually uses port 80 for HTTP connections and 443 for HTTPS by default), but can use any other port.

The start (initial) request line for HTTP 1.1 is formed according to the following scheme:

> URI method HTTP/Version

For example (such a start line may indicate that the main page of the site is requested):

> GET / HTTP/1.1

**Method** is a sequence of any characters other than control and delimiters and defines the operation to be performed on the specified resource. HTTP 1.1 specification does not limit the number of different methods that can be used, but in order to meet common standards and maintain compatibility with the widest possible range of software, it usually uses only some of the most standard methods, whose meaning is explicitly disclosed in the protocol specification.

**URI** (Uniform Resource Identifier) is the path to the specific resource (for example, a document) on which you want to perform an operation (for example, when using the GET method, it means getting the resource). 

**Version** specifies which HTTP standard version is used for the request. It is specified as two numbers separated by a dot (e.g. 1.1).

An example:
> GET / HTTP/1.1
Host: example.com

### The difference between the HTTP protocol versions

### HTTP 1.1
The first standardized version of the HTTP protocol, HTTP/1.1, was released in early 1997, a few months after the release of HTTP/1.0. At the time of its release, HTTP/1.1 supported 7 methods: GET, POST, PUT, DELETE, HEAD, OPTIONS, TRACE. However, later, in 2010, the PATCH method was added to the standard, and then in 2014 the CONNECT method.

HTTP/1.1 protocol turned out to be very successful and has served more than 15 years in its original version. During its use, only the HTTPS protocol extension appeared to provide encrypted data transfer between the browser and the server using the mechanisms of SSL/TLS.

### HTTP/2
HTTP/2 aims to use network resources more efficiently and reduce apparent latency. This has led to a new binary data format layer that is not backward compatible with HTTP/1.x servers and clients.

The first draft of HTTP/2 was based on the SPDY specification, which was released in 2015. Important aspects were parallelization, prioritization, and stream control:

* A stream is a bidirectional transfer of data within an established TCP connection.
* The transfer is made over a single TCP connection with any number of parallel streams.
* Such a protocol is called a multiplexed protocol. Multiple parallel requests can use the same connection.
* This provides an opportunity for different prioritization of transferred data.
* It also allows the server to initiate data transfer independently.
* Instead of textual data, the protocol uses a binary data format, which increases performance and security.
* The request and response headers are automatically compressed.

### HTTP/3

With the advent of smartphones and many other portable devices with wireless connectivity, the overall amount of web traffic has increased dramatically. HTTP/2 running over TCP, with its head-of-line blocking problem, could cause delays in requests and responses. Because TCP provides strict packet sequencing, a problem with one slow packet could slow or even stop the entire stream. Also, HTTP/2 did not have a strict requirement for data encryption, and there were still security issues with intercepting request and response headers.

HTTP/3 is designed to address these issues, and is now being tested with a published specification. The new protocol should address current speed, reliability, and security issues for a wide range of devices.

Instead of TCP, HTTP/3 is based on a new protocol called QUIC, which has been under development at Google since 2012. QUIC works over UDP (User Datagram Protocol).
QUIC itself provides multiplexing, and the loss of a packet will only affect the stream that has a connection to that packet, the other streams within the connection will continue to work. Request and response headers are compressed by QPACK instead of HPACK in HTTP/2.
TLS 1.3 is used for encryption, which is effectively used in HTTPS.
The latest versions of Chrome, Firefox, Edge, Opera, and some mobile browsers already support HTTP/3, but it requires server support to work.

According to statistics from w3techs.com, as of July 2021, 45.7% of websites are accessible via HTTP/2 and only 20% via HTTP/3.

### How to read the response?

The response looks like this:
> HTTP/Version Status-Code Reason-Phrase

**Version** of the protocol is set in the same way as in the request.

**Status code** is a three-digit number (the first of which indicates the status class) that defines the result of the request. For example, if the GET method was used and the server provides a resource with the specified identifier, then such a status is specified with code 200. If the server reports that such a resource does not exist — 404. If the server reports that it cannot provide access to the resource because the client does not have the necessary permissions, code 403 is used. The HTTP 1.1 specification defines 40 different HTTP codes, and also allows for protocol extensions and the use of additional status codes.

The **Reason Phrase** is a textual (but not CR and LF characters) explanation of the response code, intended to make it easier for humans to read the response. The explanation may be ignored by client software and may differ from the standard in some server software implementations.

The response example:
> HTTP/1.1 200 OK
Server: nginx/1.2.1
Date: Sat, 08 Mar 2014 22:53:46 GMT
Content-Type: application/octet-stream
Content-Length: 7
Last-Modified: Sat, 08 Mar 2014 22:53:30 GMT
Connection: keep-alive
Accept-Ranges: bytes

```HTML
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
        
    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 2em;
        background-color: #fdfdff;
        border-radius: 0.5em;
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        div {
            margin: 0 auto;
            width: auto;
        }
    }
    </style>    
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is for use in illustrative examples in documents. You may use this
    domain in literature without prior coordination or asking for permission.</p>
    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>
```

You'll have to work out the headings by yourself :)


### Basics of WEB Authorization

HTTP Authentication — this protocol, described in the HTTP 1.0/1.1 standards, has been around for a very long time and is still actively used in the enterprise environment. When applied to websites, it works like this:

- When an unauthorized client accesses a protected resource, the server sends an HTTP status of "401 Unauthorized" and adds the "WWW-Authenticate" header specifying the authentication scheme and parameters.
- When the browser receives this response, it automatically displays the Username and Password dialog box. The user enters their account information.
- For all subsequent requests to this Web site, the browser automatically adds an HTTP Authorization header that passes the user's credentials to the server for authentication.
- The server authenticates the user based on the information in this header. The decision to grant access (authorization) is made separately based on the user's role, ACL, or other account information.

Let's take a look at the most common authentication methods:
* Token-based authentication;
* JWT Token;
* Oauth 2.0.
  
**Token-Based Authentication**

Also called Bearer Authentication.

Token-Based Authentication uses a signed bearer token, which the client sends to the server in the Authorization HTTP header with the Bearer keyword or in the body of the request. For example:

>Authorization: Bearer eyJhbGciOiJSUzI1NiIsImtpZCI6IjI4Y

Upon receiving a token, the server must verify its validity — that the user exists, that the time of use has not expired, and so on. Token-based authentication can be used as part of the OAuth 2.0 or OpenID Connect protocols, or the server can generate the token itself.

Any authentication method must use a protocol that provides data encryption, HTTP headers, and URLs such as HTTPS to be used securely.
 
The **JSON Web Token (JWT)** consists of three parts: Header, Payload, and Signature. The first two blocks are in JSON format and additionally base64-encoded, the payload contains arbitrary name/value pairs, and the JWT standard defines several reserved names (iss, aud, exp, and others). The signature can be created using both symmetric and asymmetric encryption algorithms. There is also a separate standard for the format of an encrypted JWT token.

>An example of a signed JWT token (after decoding blocks 1 and 2).
{ «alg»: «HS256», «typ»: «JWT» }.
{ «iss»: «auth.myservice.com», «aud»: «myservice.com», «exp»: «1435937883», «userName»: «John Smith», «userRole»: «Admin» }.
S9Zs/8/uEGGTVVtLggFTizCsMtwOJnRhjaQ2BMUQhcY

**Oauth 2.0**

OAuth 2.0 allows users to let a particular site retrieve their private data from social networks, but without giving the site their usernames/passwords. For example, when you register on the site via VK, you just give the site permission to get your name, e-mail address and other private data from VK.

### Standard HTTP methods:
- GET — Clients use GET to access resources located on the server at the specified address;
- POST — Used to send data to the server;
- PUT — Used to create or update an existing resource entirely;
- PUT — Used to update part of an existing resource;
- DELETE — Used to delete a resource.


### Postman tool for API testing

![postman](misc/images/postman.jpg)

The **Postman** program is intended for API testing, sending POST and GET requests, etc. Unlike the similar utility curl, it has a graphical interface, making it easy to learn even for beginners. 

You can download it from the [official website](https://www.postman.com/). Distributions are available for Windows, MacOS and Linux. On the latter platform, it is possible to install the utility directly from the Application Center. In any case, you start using it by signing up for a free account.

Testing the API is done by analyzing the accuracy of the output data depending on the input request. This is what Postman does: it compiles and sends them to the specified URLs, receives them back, and stores them in the database. If you like, you can store typical requests in collections (for quick access) and create different environments for them.

## Chapter III

So, let's meet the API. The result of each direction is the Postman collection. 

### Part 1. News API

First, you need to go to [here](https://newsapi.org/) and get **API KEY** (The Application Programming Interface key is a unique identifier used to authenticate the user, developer, or caller of a program).

Don't forget that **API KEY** must be used as a bearer token in the authorization header!

1. You need to get all the news on Linux.
2. Get all the news about "development" in Russian for the last 15 days.
3. Get all the news about Linux in Russian on page 3, which should have 10 news on one page.
4. Get all the headlines for "science" in Russian. 

The result of this task is a postman collection.

### Part 2. Developer Tools
And now we're going to visit hh.ru to get the data from their API (not their website). To do this, you need to open the developer console, select the "Network" tab, specify a filter to Fetch/XHR, and perform random actions on the site. You will need to get the contacts of some vacancy (look for the "Show contacts" button and click!). As a result of clicking on various buttons and links you will see requests sent to the hh.ru API in the network section (the uri request does not necessarily have to contain the "api" tag). Do the same request in Postman and make sure that the data you receive is "somewhere" on the site. So we are looking at how web applications actually work and how they communicate. (And there is no open, publicly available specification for this API.)

The resulting request must start with https://hh.ru/vacancy/...

### Part 3. Telegram bot
Today's well-known business automation tool is a ~~good site~~ Telegram Bot! Building one is now so easy, especially with the official documentation.

Writing your own bots is possible thanks to the open Telegram API. Just because it is open, there are dozens of libraries that implement available bot functions in their own way.

We're not going to write our own bot, but... Let's pull some strings provided by the official API. In this assignment, you'll practice making requests to the API via Postman, and you'll see the results right away! And you'll also see how easy it is to implement your own library to work with Telegram bots.

So, here's the task:

1. Create your own bot. It's completely free via BotFather. Don't forget to save your token!
2. Learn the format in which requests are sent to the bot via api.telegram.org.
3. Create a collection in Postman. Add subsequent requests to it.
4. Get information about the bot (getMe method).
5. Send a message to the bot (e.g. just /start).
6. Look for information about yourself in the response to the getUpdates method! Save your user_id and chat_id.
7. Now send a message to yourself on behalf of the bot (sendMessage).
8. Well, well. Now you can send a picture to yourself on behalf of the bot. Practice attaching files to the request (in the body section via form-data).
9. Now what if you attach a pdf document instead of a photo in the same sendPhoto method? The result will be surprising!
10. Now try attaching a docx file instead of a pdf document. What will be the response?
11. Finally, let's see what the bot can find out about you. For example, your photos. Try sending a request with the getUserProfilePhotos method.

The result of the task will be a Postman collection (at least 7 requests). Note: don't forget the difference between GET and POST requests!

Useful links:

- [Telegram API](https://core.telegram.org/api).
- [BotFather Guide](https://core.telegram.org/bots/features#botfather).
- [Telegram API Methods](https://core.telegram.org/methods).
