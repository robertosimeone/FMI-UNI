package com.example.chatapp.module;

import com.example.chatapp.chat.MessageType;
import jakarta.persistence.*;

@Entity
@Table(name = "messages")
public class ChatMessage {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "content")
    private String content;

    private String sender;

    private MessageType type;

    @ManyToOne
    private User user;

    public ChatMessage(String content, String sender, MessageType type, User user) {
        this.content = content;
        this.sender = sender;
        this.user = user;
        this.type = type;
    }

    public ChatMessage() {
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getSender() {
        return sender;
    }

    public void setSender(String sender) {
        this.sender = sender;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public MessageType getType() {
        return type;
    }

    public void setType(MessageType type) {
        this.type = type;
    }
}
