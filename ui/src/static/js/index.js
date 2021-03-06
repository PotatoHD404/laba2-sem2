let socket = io();

socket.on("connect", function () {
    let textarea1 = document.getElementById("consoleOutput");
    textarea1.scrollTop = textarea1.scrollHeight;
    document.getElementById("type").classList.remove("d-none");
    document.getElementById("menu").classList.add("d-none");
});

socket.on("refresh", function (data) {
    // document.getElementById("token").innerText = data.token
    document.getElementById("consoleOutput").innerHTML = data.text;
    let textarea = document.getElementById("consoleOutput");
    let temp = textarea.scrollTop;
    if (data.state !== undefined) {
        document.getElementById("polyA").value = data.state["PolyA"];
        document.getElementById("polyB").value = data.state["PolyB"];
        document.getElementById("result").value = data.state["Result"];
    }
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
socket.on("ok", function (data) {
    let  command = data['command'];
    ClearAll();
    if (command === "input") {
        document.getElementById("setInput").classList.add("is-valid");
    } else if (command === "scalarMultiply") {
        document.getElementById("scalarMultiplyInput").classList.add("is-valid");
    } else if (command === "calc") {
        document.getElementById("calcPolyInput").classList.add("is-valid");
    }
});
function ClearAll(){
    document.getElementById("setInput").classList.remove("is-invalid");
    document.getElementById("scalarMultiplyInput").classList.remove("is-invalid");
    document.getElementById("calcPolyInput").classList.remove("is-invalid");
    document.getElementById("scalarMultiplyInput").classList.remove("is-invalid");
    document.getElementById("setInput").classList.remove("is-valid");
    document.getElementById("scalarMultiplyInput").classList.remove("is-valid");
    document.getElementById("calcPolyInput").classList.remove("is-valid");
    document.getElementById("scalarMultiplyInput").classList.remove("is-valid");
}
socket.on("error", function (data) {
   let  command = data['command'];
   ClearAll();
    if (command === "input") {
        document.getElementById("setInput").classList.add("is-invalid");
    } else if (command === "scalarMultiply") {
        document.getElementById("scalarMultiplyInput").classList.add("is-invalid");
    } else if (command === "calc") {
        document.getElementById("calcPolyInput").classList.add("is-invalid");
    }
});

function ClearConsole() {
    socket.emit("clear");
}


function Command(command) {
    let json = {
        "command": command
    };
    if (command === "input") {
        json["poly"] = document.getElementById("setSelect").value;
        json["input"] = document.getElementById("setInput").value;
    } else if (command === "scalarMultiply") {
        json["poly"] = document.getElementById("scalarMultiplySelect").value;
        json["scalar"] = document.getElementById("scalarMultiplyInput").value;
    } else if (command === "calc") {
        json["poly"] = document.getElementById("calcPolySelect").value;
        json["x"] = document.getElementById("calcPolyInput").value;
    } else if (command === "type") {
        json["type"] = document.getElementById("typeSelect").value;
        document.getElementById("type").classList.add("d-none");
        document.getElementById("menu").classList.remove("d-none");
    }
    socket.emit("command", json);
}
