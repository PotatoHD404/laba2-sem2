let socket = io();
socket.on('connect', function() {
});
socket.on('refresh', function(data) {
    // console.log(data.token, data.text)
    document.getElementById('token').innerText = data.token
    document.getElementById('consoleOutput').innerText = data.text
});

function tests() {
    socket.emit('tests');
}