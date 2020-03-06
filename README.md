# My ESP8266 Projects
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/7e/NodeMCU_DEVKIT_1.0.jpg/800px-NodeMCU_DEVKIT_1.0.jpg" alt="nodemcu">

## Toggle LED_BUILTIN trough Wifi
You can easily control the pins of an ESP8266 even from the other end of the world.
This c++ function toggles the built in LED on and off (polarity is reversed because this LED is pulled to VCC):

```
server.on("/toggle", []() {
    server.send(200, "text/html", "toggled");
    if(digitalRead(LED_BUILTIN)) {
      digitalWrite(LED_BUILTIN, 0);
    } else {
      digitalWrite(LED_BUILTIN, 1);
    }
  });
```

On the client side one can simply send a fetch command to the __/toggle__ endpoint:

```html
<meta name='viewport' content='width=device-width, initial-scale=1'>
<style>body{text-align:center;}button{padding:20px;}</style>
<h1>Toggle LED_BUILTIN</h1>
<button id='button' onclick='toggle()'>Toggle</button>
<script>
const toggle = () => {
	fetch('http://192.168.0.179/toggle');
}
</script>
```