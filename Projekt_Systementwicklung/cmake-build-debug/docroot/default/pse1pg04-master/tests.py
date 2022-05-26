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
host = '127.0.0.1'
port = 31337

# Overwrite host and port (if specified)
if len(sys.argv) == 3:
    _, host, port = sys.argv
    port = int(port)

# Initialise Laz0rCannon
cannon = Laz0rCannon(host=host, port=port)

# Laz0r Beams (Tests to fire against the server).

cannon += Beam(
	description='Host mit vielen Leerzeichen',
	request='GET /index.html HTTP/1.1\r\nHOST:                  extern\r{host}:{port}\r\n\r\n',
	response=['HTTP/1.1 200']
)

cannon += Beam(
	description='Anfrage ohne alles',
	request=' \r\nHOST:extern\r{host}:{port}\r\n\r\n',
	response=['HTTP/1.1 400']
)

cannon += Beam(
	description='Index aus extern',
	request='GET /index.html HTTP/1.1\r\nHOST:extern\r{host}:{port}\r\n\r\n',
	response=['HTTP/1.1 200']
)

cannon += Beam(
	description='Index aus intern',
	request='GET /index.html HTTP/1.1\r\nHOST:intern\r{host}:{port}\r\n\r\n',
	response=['HTTP/1.1 401']
)

cannon += Beam(
	description='Ganz normaler Aufruf',
	request='GET /default/index.html HTTP/1.1\r\nHOST: \r{host}:{port}\r\n\r\n',
	response=['HTTP/1.1 200']
)


cannon += Beam(
	description='encoded Pfad',
	request='GET /default/DATEI%20mit%20%25/index.html HTTP/1.1\r\nHOST: \r{host}:{port}\r\n\r\n',
	response=['HTTP/1.1 200']
)

cannon += Beam(
	description='decoded Pfad',
	request='GET /default/DATEI mit %/index.html HTTP/1.1\r\nHOST: \r {host}:{port}\r\n\r\n',
	response=['HTTP/1.1 400']
)

cannon += Beam(
	description='Host falsch geschrieben',
	request='GET /index.html HTTP/1.1\r\nHOOST:intern\r {host}:{port}\r\n\r\n',
	response=['HTTP/1.1 403']
)

cannon += Beam(
	description='Falscher Host',
	request='GET /index.html HTTP/1.1\r\nHOST:internnn\r {host}:{port}\r\n\r\n',
	response=['HTTP/1.1 403']
)

cannon += Beam(
    description='auserhalb der DocRoot',
    request='GET /../extern HTTP/1.1\r\nhOsT:\r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 403']
)

cannon += Beam(
    description='Kauderwelsch',
    request='[1] schwer- oder unverständliche Sprache; aus Elementen verschiedener Sprachen gemischte Ausdrucksweise, fehlerhafte Ausdrucksweise',
    response=['HTTP/1.1 501']
)

cannon += Beam(
    description='Groß- und Kleinbuchstaben abwechselnd in Host-Header',
    request='GET /default/index.html HTTP/1.1\r\nhOsT:\r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)

cannon += Beam(
    description='Keine Ressource angegeben',
    request='GET  HTTP/1.1\r\nHost:\r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

cannon += Beam(
    description='Zu viele Zeichen',
    request='GET /aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaindex.html  HTTP/1.1\r\nHost: \r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 414']
)
cannon += Beam(
    description='Keine Http-Version angegeben',
    request='GET /default/index.html\r\nHost: \r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

cannon += Beam(
    description='Ungültiges Http-Verb "POST"',
    request='POST /default/index.html HTTP/1.1\r\nHost:\r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 501']
)

cannon += Beam(
    description='Http-Verb in Kleinbuchstaben (get)',
    request='get /index.html HTTP/1.1\r\nHost:\r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 501']
)

cannon += Beam(
    description='zu viele Leerzeichen',
    request='GET                            /default/index.html                     HTTP/1.1\r\nhOsT: \r{host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)


# Pew pew!
cannon.pewpew()