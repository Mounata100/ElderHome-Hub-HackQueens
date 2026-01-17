const output = document.getElementById("output");
const DATA = {
  food: [
    { name: "Chicken Rice", img: "img/food/chicken.jpg" },
    { name: "Fishball Noodles", img: "img/food/noodles.jpg" },
    { name: "Vegetarian Meal", img: "img/food/veg.jpg" }
  ],
  groceries: [
    { name: "Milk", img: "img/groceries/milk.jpg" },
    { name: "Eggs", img: "img/groceries/eggs.jpg" },
    { name: "Bread", img: "img/groceries/bread.jpg" }
  ],
  transport: [
    { name: "Taxi", img: "img/transport/taxi.jpg" },
    { name: "Community Shuttle", img: "img/transport/shuttle.jpg" },
    { name: "Ambulance", img: "img/transport/ambulance.jpg" }
  ]
};


function speak(text) {
  const msg = new SpeechSynthesisUtterance(text);
  speechSynthesis.speak(msg);
}

function show(text) {
  output.innerText = text;
  speak(text);
}

/*function orderFood() {
  fetch("http://localhost:3000/food")
    .then(res => res.json())
    .then(data => {
      show(`Your lunch is on the way. ETA ${data.eta}`);
    });
}
*/

/*function bookAppointment() {
  fetch("http://localhost:3000/appointment")
    .then(res => res.json())
    .then(data => {
      show(`Appointment confirmed at ${data.time}`);
    });
}*/

function bookAppointment() {
  output.innerHTML = `
    <h2>Select Time</h2>
    <button onclick="confirmAppt('9:30 AM')">9:30 AM</button>
    <button onclick="confirmAppt('10:20 AM')">10:20 AM</button>
  `;
}

function confirmAppt(time) {
  show(`Appointment confirmed at ${time}`);
}


function buyGroceries() {
  show("Your usual groceries have been reordered.");
}

/*function showMedicine() {
  output.innerHTML = `
    <h2>Medicine Reminder</h2>
    <p>Morning: Amlodipine</p>
    <button onclick="markTaken()">TAKEN</button>
  `;
}

function markTaken() {
  show("Good job aunty. Medicine recorded.");
}


function medicineRefill() {
  show("Your medicine will arrive on Thursday.");
}
*/

function medicineRefill() {
  showMedicine();
}

function showMedicine() {
  output.innerHTML = `
    <div class="medicine-box">
      <h2>💊 Medicine Today</h2>

      <div class="med-item">
        <p><strong>Morning</strong></p>
        <p>Amlodipine 5mg</p>
        <button onclick="markTaken('Amlodipine')">TAKEN</button>
      </div>

      <div class="med-item">
        <p><strong>Evening</strong></p>
        <p>Metformin 500mg</p>
        <button onclick="markTaken('Metformin')">NOT YET</button>
      </div>

      <hr>

      <button class="refill" onclick="confirmRefill()">REFILL MEDICINE</button>
      <button onclick="goHome()">BACK</button>
    </div>
  `;
}

function markTaken(med) {
  speak(`Good job aunty. ${med} taken.`);
  output.innerHTML = `
    <h2>✅ Thank You</h2>
    <p>${med} recorded as taken.</p>
    <button onclick="showMedicine()">BACK TO MEDICINE</button>
  `;
}
function confirmRefill() {
  fetch("http://localhost:3000/medicine-refill", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ elder: "Mdm Tan" })
  });

  speak("A nurse has been notified to refill your medicine.");
  output.innerHTML = `
    <h2>📦 Refill Requested</h2>
    <p>A nurse will arrange your medicine.</p>
    <p>Expected delivery: Thursday</p>
    <button onclick="goHome()">OK</button>
  `;
}
function goHome() {
  output.innerHTML = "";
}


function bookTransport() {
  show("Taxi booked for 9 AM.");
}

function help() {
  fetch("http://localhost:3000/help", { method: "POST" });
  show("Help request sent. Your guardian has been notified.");
}

function orderFood() {
  document.getElementById("output").innerHTML = `
    <h2>What would you like to eat?</h2>
    <div class="food-grid">
      <img src="img/chicken.jpg" onclick="selectFood('Chicken Rice')">
      <img src="img/noodles.jpg" onclick="selectFood('Fishball Noodles')">
      <img src="img/veg.jpg" onclick="selectFood('Vegetarian Meal')">
      <img src="img/indian.jpg" onclick="selectFood('Indian Set')">
    </div>
  `;
}

function selectFood(food) {
  fetch("http://localhost:3000/food", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ food })
  });

  speak(`You selected ${food}. A nurse has been notified.`);
  show(`You selected ${food}. A nurse will arrange delivery.`);
}


/* Voice input */
function startVoice() {
  const recognition = new webkitSpeechRecognition();
  recognition.lang = "en-SG";
  recognition.start();

  recognition.onresult = function(event) {
    const text = event.results[0][0].transcript.toLowerCase();
    if (text.includes("food")) orderFood();
    else if (text.includes("appointment")) bookAppointment();
    else if (text.includes("help")) help();
    else show("Sorry aunty, I didn't understand.");
  };
}
