package com.example.chatapp.config;

import com.example.chatapp.chat.ChatMessageDTO;
import com.example.chatapp.chat.MessageType;
import com.example.chatapp.service.ChatMessageService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.context.event.EventListener;
import org.springframework.messaging.simp.SimpMessageSendingOperations;
import org.springframework.messaging.simp.stomp.StompHeaderAccessor;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.messaging.SessionDisconnectEvent;

@Component
@RequiredArgsConstructor
@Slf4j
public class WebSocketEventListener {

    private final SimpMessageSendingOperations messageTemplate;

    private final ChatMessageService chatService;

    @EventListener
    public void handleWebSocketDisconnectListener(SessionDisconnectEvent event) {
        StompHeaderAccessor headerAccessor = StompHeaderAccessor.wrap(event.getMessage());
        String username = (String) headerAccessor.getSessionAttributes().get("username");
        if(username != null) {
            log.info("User disconnected: {}", username);
            var chatMessage = ChatMessageDTO.builder()
                    .sender(username)
                    .type(MessageType.LEAVE)
                    .build();
            chatService.saveMessage(chatMessage);
            messageTemplate.convertAndSend("/topic/public", chatMessage);
        }
    }
}
