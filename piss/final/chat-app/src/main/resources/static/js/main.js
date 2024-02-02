'use strict';

var usernamePage = document.querySelector('#username-page');
var chatPage = document.querySelector('#chat-page');
var loginPage = document.querySelector('#login-page');
var registerForm = document.querySelector('#registerForm');
var loginForm = document.querySelector('#loginForm')
var messageForm = document.querySelector('#messageForm');
var messageInput = document.querySelector('#message');
var messageArea = document.querySelector('#messageArea');
var connectingElement = document.querySelector('.connecting');

var stompClient = null;
var username = null;
var fullname = null;
var password = null;
var repeatPassword = null;

var colors = [
    '#4da8f8', '#35b13f', '#00BCD4', '#ff5652',
    '#ffc507', '#d04a86', '#ff9100', '#b239bb'
];

function register(event) {
    username = document.querySelector('#username').value.trim();
    fullname = document.querySelector('#fullname').value.trim();
    password = document.querySelector('#password').value.trim();
    repeatPassword = document.querySelector('#repeat-password').value.trim();
    if(password !== repeatPassword) {
        alert("Password should be the same as repeat password!");
        registerForm.reset();
        return;
    }
    if (username && fullname) {
        usernamePage.classList.add('hidden');
        loginPage.classList.add('hidden');
        chatPage.classList.remove('hidden');

        var socket = new SockJS('/ws');
        stompClient = Stomp.over(socket);

        stompClient.connect({}, onRegister, onError);
    }
    event.preventDefault();
}

function login(event) {
    username = document.querySelector('#usernameLogin').value.trim();
    password = document.querySelector('#passwordLogin').value.trim();
    if (username && password) {
        usernamePage.classList.add('hidden');
        loginPage.classList.add('hidden');
        chatPage.classList.remove('hidden');

        var socket = new SockJS('/ws');
        stompClient = Stomp.over(socket);

        stompClient.connect({}, onLogin, onError);
    }
    event.preventDefault();
}

async function onConnect() {
    await getMessageHistory();

    stompClient.subscribe('/topic/public', onMessageReceived);

    stompClient.send("/app/chat.addUser",
        {},
        JSON.stringify({sender: username, type: 'JOIN'})
    )

    connectingElement.classList.add('hidden');
}

async function onRegister() {
    await fetch('/register', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({username: username,
            fullname: fullname,
            password: password,
            status: 'ONLINE'})
    }).then(response => {
        if (!response.ok) {
            usernamePage.classList.remove('hidden');
            chatPage.classList.add('hidden');
            alert('Username already exists');
            return;
        }
        onConnect();
        return response.json();
    })
}

async function onLogin() {

    await fetch('/login', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            username: username,
            password: password,
            status: 'ONLINE'})
    }).then(response => {
        if (!response.ok) {
            loginPage.classList.remove('hidden');
            chatPage.classList.add('hidden');
            alert('Error loggin in');
            return;
        }
        onConnect();
        return response.json();
    })
}

function loadLogin() {
    usernamePage.classList.add('hidden');
    loginPage.classList.remove('hidden');
}

function loadRegister() {
    usernamePage.classList.remove('hidden');
    loginPage.classList.add('hidden');
}

function onError(error) {
    connectingElement.textContent = 'Could not connect to WebSocket server. Please refresh this page to try again!';
    connectingElement.style.color = 'red';
}


function sendMessage(event) {
    var messageContent = messageInput.value.trim();
    if(messageContent && stompClient) {
        var chatMessage = {
            sender: username,
            content: messageInput.value,
            type: 'CHAT'
        };
        stompClient.send("/app/chat.sendMessage", {}, JSON.stringify(chatMessage));
        messageInput.value = '';
    }
    event.preventDefault();
}

function loadMessage(message) {
    if(message.sender === null) {
        alert('User is not registered');
        usernamePage.classList.remove('hidden');
        chatPage.classList.add('hidden');
        return;
    }
    var messageElement = document.createElement('li');

    if(message.type === 'JOIN') {
        messageElement.classList.add('event-message');
        message.content = message.sender + ' joined!';
    } else if (message.type === 'LEAVE') {
        messageElement.classList.add('event-message');
        message.content = message.sender + ' left!';
    } else {
        messageElement.classList.add('chat-message');

        var avatarElement = document.createElement('i');
        var avatarText = document.createTextNode(message.sender[0]);
        avatarElement.appendChild(avatarText);
        avatarElement.style['background-color'] = getAvatarColor(message.sender);

        messageElement.appendChild(avatarElement);

        var usernameElement = document.createElement('span');
        var usernameText = document.createTextNode(message.sender);
        usernameElement.appendChild(usernameText);
        messageElement.appendChild(usernameElement);
    }

    var textElement = document.createElement('p');
    var messageText = document.createTextNode(message.content);
    textElement.appendChild(messageText);

    messageElement.appendChild(textElement);

    messageArea.appendChild(messageElement);
    messageArea.scrollTop = messageArea.scrollHeight;
}

function onMessageReceived(payload) {
    var message = JSON.parse(payload.body);
    loadMessage(message);
}


function getAvatarColor(messageSender) {
    var hash = 0;
    for (var i = 0; i < messageSender.length; i++) {
        hash = 31 * hash + messageSender.charCodeAt(i);
    }
    var index = Math.abs(hash % colors.length);
    return colors[index];
}

async function getMessageHistory() {
    const historyResponse = await fetch('/history');
    let historyMessages = await historyResponse.json();
    historyMessages.forEach(message => loadMessage(message));

}

registerForm.addEventListener('submit', register, true)
loginForm.addEventListener('submit', login, true)
messageForm.addEventListener('submit', sendMessage, true)