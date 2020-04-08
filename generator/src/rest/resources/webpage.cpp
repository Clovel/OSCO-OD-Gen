/** 
 * Let There Be Light project
 * 
 * @file webpage.cpp
 */

/* Includes -------------------------------------------- */
#include "webpage.hpp"

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */
/* Web page variables ---------------------------------- */
const char * const htmlResponseCode200 = R"=====(HTTP/1.1 200 OK
Content-type:text/html
Connection: close
)=====";

const char * const htmlResponseCode400 = R"=====(HTTP/1.0 400 BAD REQUEST
Content-Type: text/html
Connection: close

<!DOCTYPE html>
<html lang ="en">
    <head>
        <title>400 - BAD REQUEST</title>
    </head>
    <body>
        Your browser sent a bad request, 
        such as a POST without a Content-Length.
    </body>
</html>
)=====";

const char * const htmlResponseCode404 = R"=====(HTTP/1.0 404 NOT FOUND
Content-Type: text/html
Connection: close

<!DOCTYPE html>
<html lang ="en">
    <head>
        <title>404 - Not found</title>
    </head>
    <body>
        The server could not fulfill your request because the resource specified"
        is unavailable or nonexistent.
        <br>"
            Please check that you entered the correct URL.
        </br>
    </body>
</html>
)=====";

const char * const htmlResponseCode500 = R"=====(HTTP/1.0 500 Server internal error
Content-Type: text/html
Connection: close

<!DOCTYPE html>
<html lang ="en">
    <head>
        <title>500 - Server internal error</title>
    </head>
    <body>
        Server-side error prohibited execution.
    </body>
</html>
)=====";

const char * const htmlResponseCode501 = R"=====(HTTP/1.1 501 Method Not Implemented
Content-type:text/html
Connection: close

<!DOCTYPE html>
<html lang="en">
    <head>
        <title>
            501 - Method Not Implemented
        </title>
    </head>
    <body>
        HTTP request method not supported.
    </body>
</html>
)=====";

const char * const htmlDocType = R"=====(<!DOCTYPE html>
)=====";

const char * const htmlPageBegin = R"=====(<html lang="en">
)=====";

const char * const htmlPageEnd = R"=====(</html>

)=====";

// CSS to style the on/off buttons 
// Feel free to change the background-color and font-size attributes to fit your preferences
const char * const htmlHead = R"=====(
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
        <style>
        html {
            font-family: Helvetica;
            display: inline-block;
            margin: 0px auto;
            text-align: center;
        }
        .button {
            background-color: #195B6A;
            border: none;
            color: white;
            padding: 16px 40px;
            text-decoration: none;
            font-size: 30px;
            margin: 2px;
            cursor: pointer;
        }
        .button2 {
            background-color: #77878A;
        }
        </style>
    </head>
)=====";

const char * const htmlGeneralKenobi = R"=====(
    <html lang ="en">
        <head>
            <title>web-example</title>
        </head>
        <body>
            - Hello there !
            - General Kenobi !
        </body>
    </html>
)=====";
