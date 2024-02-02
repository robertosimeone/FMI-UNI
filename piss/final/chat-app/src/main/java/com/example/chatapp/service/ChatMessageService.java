package com.example.chatapp.service;

import com.example.chatapp.chat.ChatMessageDTO;
import com.example.chatapp.module.ChatMessage;
import com.example.chatapp.module.User;
import com.example.chatapp.repository.ChatMessageRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class ChatMessageService {

    private final ChatMessageRepository repository;

    private final UserService userService;

    public void saveMessage(ChatMessageDTO messageDTO) {
        User user = userService.getUserByUsername(messageDTO.getSender());
        ChatMessage message = messageDTO.toEntity(user);
        repository.save(message);
    }

    public List<ChatMessageDTO> getMessages() {
        return repository.findAll().stream()
                .map(this::toDto)
                .collect(Collectors.toList());
    }

    public ChatMessageDTO toDto(ChatMessage message) {
        return ChatMessageDTO.builder()
                .sender(message.getSender())
                .content(message.getContent())
                .type(message.getType())
                .build();
    }
}
