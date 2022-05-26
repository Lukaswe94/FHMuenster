#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# This script makes a HTTP request to a specific server and compares
# responses with user-defined expected responses.
from __future__ import unicode_literals

import sys

from pewpewlaz0rt4nk import (
    Beam,
    Laz0rCannon,
)

__version__ = '2.0.0'

# Set host and port.
# Read the target IP address and port from the command line arguments.
# If there are no command line arguments, use the following default values.
host = 'localhost'
port = 31337

# Overwrite host and port (if specified)
if len(sys.argv) == 3:
    _, host, port = sys.argv
    port = int(port)

# Initialise Laz0rCannon
cannon = Laz0rCannon(host=host, port=port)

# Laz0r Beams (Tests to fire against the server).
#------200 HTTP Requests-----#
cannon += Beam(
    description='HTTP 1.0 Request',
    request='GET /index.html HTTP/1.0\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 505']
)
cannon += Beam(
    description='HTTP 1.1 Request',
    request='GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Umlaute im html Dateinamen',
    request='GET /äöü.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Host in different cases',
    request='GET /index.html HTTP/1.1\r\nHOsT: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Host on different position in Header',
    request='GET /index.html HTTP/1.1\r\nConnection: close\r\nHOsT: {host}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Host in lowercase',
    request='GET /index.html HTTP/1.1\r\nConnection: close\r\nhost: {host}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Host in uppercase',
    request='GET /index.html HTTP/1.1\r\nConnection: close\r\nHOST: {host}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Requests extern',
    request='GET /index.html HTTP/1.1\r\nHost: extern:{port}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Spaces in request in front of "GET"',
    request='            GET /index.html HTTP/1.1\r\nConnection: close\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Spaces in Host',
    request='GET /index.html HTTP/1.1\r\nHost: extern:    {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Spaces in front of Host',
    request='GET /index.html HTTP/1.1\r\nHost:                extern: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Spaces after get',
    request='GET                     /index.html HTTP/1.1\r\nConnection: close\r\nHost:               {host}       \r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Requests intern Success',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic dGVzdDp0ZXN0dGVzdA==\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
#------Images-----#
cannon += Beam(
    description='Ein JPG-Bild',
    request='GET /images/tux.jpg HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Ein PNG-Bild',
    request='GET /images/tux.png HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Ein PNG-Bild mit grossen Buchstaben',
    request='GET /images/TUX1.PNG HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Ein PNG-Bild mit Leerzeichen',
    request='GET /images/ein%20leerzeichen.png HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Ein PNG-Bild ohne Punkt',
    request='GET /images/tux HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Ein PNG-Bild mit ziemlich langem Dateinamen',
    request='GET /images/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.png HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Ein PNG-Bild mit RICHTIG langem Dateinamen',
    request='GET /images/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.png HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 414']
)
#------JAVASCRIPT-----#
cannon += Beam(
    description='Ein PNG-Bild ohne Punkt',
    request='GET /js/javascript.js HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
#------400-----#
cannon += Beam(
    description='\\n in front of host',
    request='GET /index.html HTTP/1.1\r\nHost: \n{host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='\\r in front of host',
    request='GET /index.html HTTP/1.1\r\nHost: \r{host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='Spaces in Host',
    request='GET',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='No ressource"',
    request='GET                      HTTP/1.1\r\nConnection: close\r\nHost:               {host}       \r\n\r\n',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='No ressource"',
    request='GET                      HTTP/1.1\r\nConnection: close\r\nHost:               {host}       \r\n\r\n',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='missing / in front of index.html',
    request='GET index.html HTTP/1.1\r\nConnection: close\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 400']
)
#------401-----#
cannon += Beam(
    description='Requests intern',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Requests intern wrong login',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic aGVsbG86aGVsbG93b3JsZA==\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Requests intern wrong username',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic dGVzOnRlc3R0ZXN0\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Requests intern wrong password',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic dGVzdDplc3R0ZXN0\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Requests intern missing :',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic dGVzdHRlc3R0ZXN0\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Requests intern starts with :',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic OnRlc3Q6dGVzdHRlc3Q=\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Requests intern ends with :',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic dGVzdDp0ZXN0dGVzdDo=\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Requests intern basic without Sha64',
    request='GET /index.html HTTP/1.1\r\nHost: intern:{port}\r\nAuthorization: Basic \r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 401']
)
#------403-----#
cannon += Beam(
    description='file exists but not in docRoot',
    request='GET /../../index.html HTTP/1.1\r\nConnection: close\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 403']
)
#------404-----#
cannon += Beam(
    description='index.txt',
    request='GET /index.txt HTTP/1.1\r\nConnection: close\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='/test',
    request='GET /test HTTP/1.1\r\nConnection: close\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='filenotexist.html',
    request='GET /filenotexist.html HTTP/1.1\r\nConnection: close\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='file is not existing and not in docRoot',
    request='GET /../../indx.html HTTP/1.1\r\nConnection: close\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='Images folder',
    request='GET /images HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 404']
)
#------501-----#
cannon += Beam(
    description='Non-existsing HTTP-Method',
    request='test /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)
cannon += Beam(
    description='Invalid HTTP-Method',
    request='POST /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)
#------505-----#
cannon += Beam(
    description='HTTP 1.4 Request',
    request='GET /index.html HTTP/1.4\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 505']
)
cannon += Beam(
    description='HTTP 14 Request',
    request='GET /index.html HTTP/14\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 505']
)

# Pew pew!
cannon.pewpew()
