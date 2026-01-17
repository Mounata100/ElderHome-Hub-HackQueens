const express = require("express");
const app = express();
const cors = require("cors");
const path = require("path");

app.use(cors());
app.use(express.json());

// ✅ Serve frontend
app.use(express.static(path.join(__dirname, "../frontend")));

app.get("/food", (req, res) => {
  res.json({ eta: "1:15 PM" });
});

app.get("/appointment", (req, res) => {
  res.json({ time: "10:20 AM with Dr Tan" });
});

app.post("/help", (req, res) => {
  console.log("🚨 Guardian notified");
  res.sendStatus(200);
});

app.listen(3000, () => {
  console.log("Server running at http://localhost:3000");
});




/*const express = require("express");
const app = express();
const cors = require("cors");

app.use(cors());
app.use(express.json());

app.get("/food", (req, res) => {
  res.json({ eta: "1:15 PM" });
});

app.get("/appointment", (req, res) => {
  res.json({ time: "10:20 AM with Dr Tan" });
});

app.post("/help", (req, res) => {
  console.log("🚨 Guardian notified via WhatsApp");
  res.sendStatus(200);
});

app.listen(3000, () => {
  console.log("Backend running on http://localhost:3000");
});
*/