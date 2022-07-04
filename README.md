# Enigma-Simulation
> A simulation of a German encryption machine called Enigma used in WW2

## Enigma Machine
Enigma machines cycle through a string character by character, performing a number of distinct operations on the current character to convert it and when those new characters are combined again, the final product is the encrypted message. During the early 20th century, Enigma was one of the most powerful cyphering tool and was considered "impossible" to crack. However, this did not stop some mathematicians from cracking the code. Alan Turing and other Polish mathematicians were able to decrypt the hidden german messages by building the first computer during WW2 which helped save the Allied Powers.

### Cycle of Conversion Operations
Each character goes through a cycle of operations that go in the following order:
- Plugboard
- 3 Rotors (going forward)
- Reflector
- 3 Rotors (going backward)
- Plugboard

> **Plugboard** => A board with letters and there are ~10 plugs which pair 2 letters. So when there is an eletrical signal that passes through the plugboard it swaps the letter if it is plugged in with a different letter. <br>
> **Rotor** => A wheel with random letters connected with other random letters through a bunch of random wiring and the connections can be cycled through by rotating the wheel so they connections will not always be the same. Each rotor has a notch to determine how many wheels will be spinning so the connections can be changed accordingly. <br>
> **Reflector** => After passing through the 3 rotors normally and converting the character 3 times and spinning the rotors, the reflector again filled with random wiring swaps the letter and sends it back through the rotors in reverse order back to the plugboard.

## Simulation
This simulation is a C++ implementation of the Enigma Machine. It generates a random Enigma setting for the day, and allows you to encrypt any message that you want.

### Possible Settings

*The method I used to display connections in rotors and reflectors down below is by using maps.*
```
current letter = D (position 4 in the alphabet)
map = "EKM(F)LGDQVZNTOWYHXUSPAIBRCJ"
converted letter = D -> F
```
- Rotor Wheels (8):
```
Rotor I: map="EKMFLGDQVZNTOWYHXUSPAIBRCJ", notch="R"
Rotor II: map="AJDKSIRUXBLHWTMCQGZNPYFVOE", notch="F"
Rotor III: map="BDFHJLCPRTXVZNYEIWGAKMUSQO", notch="W"
Rotor IV: map="ESOVPZJAYQUIRHXLNFTGKDCMWB", notch="K"
Rotor V: map="VZBRGITYUPSDNHLXAWMJQOFECK", notch="A"
Rotor VI: map="JPGVOUMFYQBENHZRDKASXLICTW", notch="AN"
Rotor VII: map="NZJHGRCXMYSWBOUFAIVLPEKQDT", notch="AN"
Rotor VIII: map="FKQHTLXOCBJSPDZRAMEWNIUYGV", notch="AN"

Each set of 3 rotors has 26^3 possibilities because of all of the spinning and stepping in the
wheels and since we pass those 3 sets of rotors twice it technically counts as passing 6 rotor
which would mean that passing through the rotors alone creates 26^6 possibilities.
There are 8 wheels in total out of which 3 rotors will be selected everyday which adds another 
P(8,3) permutations.
This means that there are P(8,3)*26^3 possibilities of conversions from the rotors alone which 
is ~103,795,700,736
```
- Plugboard:
```
10 pairs of any 2 letters in the English Alphabet
(i.e. AE BL DW FK GO IU JN MR QS ZX)

Each of the 20 extremities of the 10 wires can be plugged into any of the 26 positions that are 
not occupied, with the two extremities of a given wire equivalent, as well as the 10 wires themselves.
This means that there are 26!/((26−20)!⋅2^(10)⋅10!) possible combinations from the plugboard 
with is ~150,738,274,937,250
```
- Reflector (3):
```
Reflector A: map="EJMZALYXVBWFCRQUONTSPIKHGD"
Reflector B: map="YRUHQSLDPXNGOKMIEBFZCWVJAT"
Reflector C: map="FVPJIAOYEDRZXWGCTKUQSBNMHL"

Each reflector only has 25 conversion possibilties for a character. However, since there are 3 
possible reflectors to choose from there are P(3,1) permutations possible.
This means that there are P(3,1)*25 possibilities for the reflectors which is ~75
```

When we see all of these components combined together to form an Enigma machine we see that there
are approximately `P(8,3)*26^6 * 26!/((26−20)!⋅2^(10)⋅10!) * P(3,1)*25 = 1,173,448,865,613,576,763,411,200,000` 
possible Enigma settings in this simulation.

----

**So, heres my challenge to you. Can you decipher the encrypted Enigma messages returned from the simulation without looking at the daily enigma settings?**
