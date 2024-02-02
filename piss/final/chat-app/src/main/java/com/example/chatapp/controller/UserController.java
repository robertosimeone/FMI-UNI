package com.example.chatapp.controller;

import com.example.chatapp.module.User;
import com.example.chatapp.service.UserService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

@Controller
@RequiredArgsConstructor
@Slf4j
public class UserController {

    private final UserService service;

    @PostMapping("/register")
    public ResponseEntity<User> addUser(@RequestBody User user) {
        ResponseEntity<User> response = new ResponseEntity<>(service.saveUser(user), HttpStatus.CREATED);
        log.info("User registered sccessfully: {}", user.getUsername());
        return response;
    }

    @PostMapping("/login")
    public ResponseEntity<User> logUser(@RequestBody User user) {
        ResponseEntity<User> response = new ResponseEntity<>(service.logUser(user), HttpStatus.OK);
        log.info("User logged into the system successfully: {}", user.getUsername());
        return response;
    }

}
