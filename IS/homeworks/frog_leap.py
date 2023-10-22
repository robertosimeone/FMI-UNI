import copy
import time

def isSolved(board):
    n = int((len(board)-1)/2)
    emptyIndex = n
    if board.index('_') != n:
        return False
    for  counter in range(0,n):
        if board[counter] != '<':
            return False
    return True  
    
def frog_leap(board,emptyIndex,stack):
    if isSolved(board):
        return True
    for _board in available_boards(board):
        if frog_leap(_board,_board.index('_'),stack):
            stack.append(_board)
            return True
    return False
    
def frog_leap_calculation(n):
    start = time.time()
    board = ['>' for x in range(0,n)] + ['_'] + ['<' for x in range(0,n)]
    stack = []
    frog_leap(board,n,stack)
    print(len(stack))
    print(board)
    for i in range(0,len(stack)):
        print(stack.pop(-1))
    end = time.time()
    print(end-start)

def available_boards(board):
    emptyIndex = board.index('_')
    possible_moves = [emptyIndex+x for x in range(-2,3) if emptyIndex+x>=0 and emptyIndex+x<=len(board)-1 and x!=0]
    possible_boards = []
    for addend in possible_moves:
        if (addend<emptyIndex and board[addend] == '>') or (addend>emptyIndex and board[addend] == '<'):
                new_board = copy.copy(board)
                new_board[addend],new_board[emptyIndex] = new_board[emptyIndex],new_board[addend]
                possible_boards.append(new_board)
    return possible_boards

frog_leap_calculation(20)
# RL_RR