#!/usr/bin/env python3
"""
Mental Health Companion - Local Server
Simple HTTP server to run the application on localhost
"""

import http.server
import socketserver
import socket
import webbrowser
import os
from pathlib import Path

# Configuration
PORT = 8000
DIRECTORY = Path(__file__).parent


def find_available_port(start_port):
    port = start_port
    while port <= 8100:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            if sock.connect_ex(("127.0.0.1", port)) != 0:
                return port
        port += 1

    raise OSError("No free port found in range 8000-8100")


class ReusableTCPServer(socketserver.TCPServer):
    allow_reuse_address = True

class CustomHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(DIRECTORY), **kwargs)
    
    def end_headers(self):
        # Add security headers
        self.send_header('X-Content-Type-Options', 'nosniff')
        self.send_header('X-Frame-Options', 'DENY')
        self.send_header('X-XSS-Protection', '1; mode=block')
        self.send_header('Cache-Control', 'no-store, no-cache, must-revalidate, max-age=0')
        self.send_header('Pragma', 'no-cache')
        self.send_header('Expires', '0')
        super().end_headers()
    
    def log_message(self, format, *args):
        # Custom logging format
        print(f"[SERVER] {self.address_string()} - {format % args}")

def main():
    # Change to the script directory
    os.chdir(DIRECTORY)

    active_port = find_available_port(PORT)
    
    # Create server
    with ReusableTCPServer(("", active_port), CustomHandler) as httpd:
        url = f"http://localhost:{active_port}"
        
        print("=" * 60)
        print("🌟 Mental Health Companion Server")
        print("=" * 60)
        print(f"\n✅ Server is running!")
        print(f"📍 URL: {url}")
        print(f"📂 Directory: {DIRECTORY}")
        print(f"\n💡 Opening browser automatically...")
        print(f"\n⚠️  Press Ctrl+C to stop the server\n")
        print("=" * 60)
        
        # Open browser automatically
        webbrowser.open(url)
        
        try:
            # Start serving
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\n\n" + "=" * 60)
            print("🛑 Server stopped by user")
            print("=" * 60)
            print("\nThank you for using Mental Health Companion! 💚")
            print("Remember to take care of your mental health!\n")

if __name__ == "__main__":
    main()
