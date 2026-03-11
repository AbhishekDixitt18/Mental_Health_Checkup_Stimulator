#!/usr/bin/env python3
"""
Mental Health Companion - Local Server
Simple HTTP server to run the application on localhost
"""

import http.server
import socketserver
import webbrowser
import os
from pathlib import Path

# Configuration
PORT = 8000
DIRECTORY = Path(__file__).parent

class CustomHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(DIRECTORY), **kwargs)
    
    def end_headers(self):
        # Add security headers
        self.send_header('X-Content-Type-Options', 'nosniff')
        self.send_header('X-Frame-Options', 'DENY')
        self.send_header('X-XSS-Protection', '1; mode=block')
        super().end_headers()
    
    def log_message(self, format, *args):
        # Custom logging format
        print(f"[SERVER] {self.address_string()} - {format % args}")

def main():
    # Change to the script directory
    os.chdir(DIRECTORY)
    
    # Create server
    with socketserver.TCPServer(("", PORT), CustomHandler) as httpd:
        url = f"http://localhost:{PORT}"
        
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
