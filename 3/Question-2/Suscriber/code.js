const mqtt = require("mqtt");

const client = mqtt.connect("mqtt://127.0.0.1", {
  clientId: "nodejsClient",
  protocolId: "MQIsdp",
  protocolVersion: 3,
  connectTimeout: 1000,
  debug: true,
  port: 1883,
});
const TOPIC = "sensors/motion";

client.on("connect", () => {
  client.subscribe(TOPIC, (err) => {
    if (!err) {
      console.log(
        `Node.js client connected to broker and subscribed to ${TOPIC}`
      );
    } else {
      console.log(err);
    }
  });
});

client.on("message", (topic, message) => {
  console.log(
    `Node.js client got the following message from ${topic}: ${message.toString()}`
  );
});

client.on("error", (err) => {
  console.log(err);
  client.end();
});

client.on("offline", () => {
  console.log("offline");
});
