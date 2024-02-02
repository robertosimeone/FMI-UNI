package com.example.chatapp.service;

import com.example.chatapp.module.Status;
import com.example.chatapp.module.User;
import com.example.chatapp.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class UserService {
    private final UserRepository repository;

    public User saveUser(User user) {
        Optional<User> userFromDb = repository.findUserByUsername(user.getUsername());
        if(userFromDb.isPresent()) {
            throw new RuntimeException("Username already exists");
        }
        repository.save(user);
        return user;
    }

    public User logUser(User user) {
        return repository.findUserByUsernameAndPassword(
                user.getUsername(), user.getPassword())
                .orElseThrow(() -> new RuntimeException("Error logging in!"));
    }

    public User getUserByUsername(String username) {
        return repository.findUserByUsername(username).orElse(null);
    }
}
