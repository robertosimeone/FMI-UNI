package com.example.chatapp.chat;

import com.example.chatapp.module.ChatMessage;
import com.example.chatapp.module.User;
import lombok.*;

import javax.annotation.processing.Generated;
import java.awt.*;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class ChatMessageDTO {
    private String content;
    private String sender;
    private MessageType type;

    public ChatMessage toEntity(User user) {
        return new ChatMessage(this.content, this.sender, this.type, user);
    }
}
