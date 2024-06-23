def nums_to_text(nums):
    rules = {0: (' ',), 2: ('A', 'B', 'C'), 3: ('D', 'E', 'F'), 4: ('G', 'H', 'I'), 5: ('J', 'K', 'L'),
             6: ('M', 'N', 'O'),
             7: ('P', 'Q', 'R', 'S'), 8: ('T', 'U', 'V'), 9: ('W', 'X', 'Y', 'Z')}
    current_num, counter, result, nums_copy = 0, 0, '', list(nums)  # creating a new list, so I can append the -1 at the
    # end and not modify the given list
    if not nums:
        return ''
    current_num = nums[0]
    nums_copy.append(-1)  # appending -1 at the end of the list ,so I don't have to check if I've reached the end of the
    # list and manually append the last letter
    for num in nums_copy:
        if current_num == num:
            counter += 1
        else:
            if current_num in rules:
                overlap = len(rules[current_num])  # saving the length of the current tuple in case we get out of range
                result = ''.join((result, rules[current_num][(counter % overlap) - 1]))
            counter = 1
            current_num = num
    return result


def text_to_nums(text):
    rules = {0: (' ',), 2: ('A', 'B', 'C'), 3: ('D', 'E', 'F'), 4: ('G', 'H', 'I'), 5: ('J', 'K', 'L'),
             6: ('M', 'N', 'O'),
             7: ('P', 'Q', 'R', 'S'), 8: ('T', 'U', 'V'), 9: ('W', 'X', 'Y', 'Z')}
    nums = []
    old_rule = -10
    for letter in text.upper():
        for rule in rules:
            if letter in rules[rule]:
                if rule == old_rule:
                    nums.append(-1)
                times = rules[rule].index(letter) + 1
                nums.extend([rule] * times)
                old_rule = rule

    return nums


def nums_to_angle(nums):
    result = 0
    for num in nums:
        if num >= 0:
            result += num
    return (result % 12) * 30


def angles_to_nums(angles):
    nums = []
    for angle in angles:
        new_angle = angle % 360  # % takes care of the negative numbers
        if 15 < new_angle <= 315:
            rem = (new_angle % 30) / 30
            new_angle = int(new_angle / 30)
            if rem > 0.5:
                nums.append(new_angle + 1)
            else:
                nums.append(new_angle)

    return nums


def is_phone_tastic(word):
    nums = text_to_nums(word)
    sum_angles = nums_to_angle(nums)
    return not sum_angles % len(word)


a = -100
print(a%360)
