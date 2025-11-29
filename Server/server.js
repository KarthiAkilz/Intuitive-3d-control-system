const WebSocket = require('ws');
const http = require('http');
const fs = require('fs');
const path = require('path');

const PORT = 8081;

// Path to your HTML
const HTML_PATH = path.join(
  __dirname,
  "Controller",
  "Joystick.html"
);

const server = http.createServer((req, res) => {
  // Always serve your main HTML file
  fs.readFile(HTML_PATH, (err, content) => {
    if (err) {
      res.writeHead(500);
      res.end("Error loading Joystick.html");
    } else {
      res.writeHead(200, { "Content-Type": "text/html" });
      res.end(content);
    }
  });
});

// WebSocket server
const wss = new WebSocket.Server({ server });

server.listen(PORT, () => {
  console.log(`🚀 Controller running at: http://192.168.31.8:${PORT}`);
});

wss.on("connection", (ws, req) => {
  console.log("📱 Client connected:", req.socket.remoteAddress);

  ws.on("message", (msg) => {
    try {
      const parsed = JSON.parse(msg);
      console.log("📨 Received:", parsed);

      // Broadcast to Unreal, etc.
      wss.clients.forEach((client) => {
        if (client !== ws && client.readyState === WebSocket.OPEN) {
          client.send(JSON.stringify(parsed));
        }
      });
    } catch (e) {
      console.warn("⚠ Invalid JSON:", e);
    }
  });

  ws.on("close", () => {
    console.log("❌ Client disconnected");
  });
});
