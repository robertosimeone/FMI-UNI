package com.example.chatapp.chat;

import com.example.chatapp.module.ChatMessage;
import com.example.chatapp.module.User;
import com.example.chatapp.service.ChatMessageService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.messaging.simp.SimpMessageHeaderAccessor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

import java.util.List;

@Controller
@RequiredArgsConstructor
@Slf4j
public class ChatController {

    private final ChatMessageService service;

    @MessageMapping("/chat.sendMessage")
    @SendTo("/topic/public")
    public ChatMessageDTO sendMessage(@Payload ChatMessageDTO chatMessageDTO) {
        service.saveMessage(chatMessageDTO);
        log.info("{} sent \"{}\" to the Chatroom", chatMessageDTO.getSender(), chatMessageDTO.getContent());
        return chatMessageDTO;
    }

    @MessageMapping("/chat.addUser")
    @SendTo("/topic/public")
    public ChatMessageDTO addUser(@Payload ChatMessageDTO chatMessageDTO, SimpMessageHeaderAccessor headerAccessor) {
        headerAccessor.getSessionAttributes().put("username", chatMessageDTO.getSender());
        service.saveMessage(chatMessageDTO);
        log.info("User joined the chat: {}", chatMessageDTO.getSender());
        return chatMessageDTO;
    }

    @GetMapping("/history")
    public ResponseEntity<List<ChatMessageDTO>> getMessageHistory() {
        return ResponseEntity.ok(service.getMessages());
    }
}

