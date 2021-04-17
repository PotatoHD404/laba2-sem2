let socket = io();

socket.on("connect", function () {
    let textarea1 = document.getElementById("consoleOutput");
    textarea1.scrollTop = textarea1.scrollHeight;
});

socket.on("refresh", function (data) {
    document.getElementById("token").innerText = data.token
    document.getElementById("consoleOutput").innerHTML = data.text
    let textarea = document.getElementById("consoleOutput");
    let temp = textarea.scrollTop;
    let interval = setInterval(() => {
        let end = textarea.scrollHeight;
        if (temp < end) {
            textarea.scrollTop += 50;
            temp += 50;
        } else {
            clearInterval(interval);
        }
    }, 5)

});
socket.on("log", function (data) {
});

function ClearConsole() {
    socket.emit("clear");
}

function RunTests() {
    socket.emit("tests");
}

function Command() {
    socket.emit("command");
}