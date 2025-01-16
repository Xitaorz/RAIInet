The Game of RAIInet

RAIInet is a C++-based command line video game similar in style to Stratego. It is played between two opposing players who take on the role of computer hackers. Each player controls eight pieces, called links. There are two different kinds of links: viruses and data. Each player has two goals:
- Download four data.
- Make their opponent download four viruses.

Upon achieving either goal, the player wins the game.

### Gameplay Overview

RAIInet is played on an 8 × 8 board. Players initially place their links face-down so that only the player who placed the link knows whether it is data or a virus. Gameplay proceeds in turns. On each turn, a player may use a single ability and then must move one of their links in any cardinal direction. 

Key mechanics include:
- Moving a link off the opponent’s end of the board to download it.
- Moving a link onto the opponent’s server ports to force them to download it.
- Engaging in battles when moving onto a space occupied by an opponent’s link.

### Links

Links are the primary game pieces, categorized as data or viruses. Each link has a strength between 1 (weakest) and 4 (strongest). Players begin the game with 8 links of various strengths.

Winning and losing conditions:
- A player wins by downloading four data.
- A player loses by downloading four viruses.

### Movement, Battle, and Capture

- Links move one space in a cardinal direction per turn.
- Links cannot occupy the same space as another friendly link or their own server ports.
- Links moved off the edge of the opponent's starting row are downloaded.
- When a link moves onto an opponent’s server port, it is downloaded by the opponent.
- When a link moves onto an opponent’s link, both links are revealed, and a battle occurs. The link with higher strength wins, and the losing link is downloaded by the winner. If strengths are tied, the initiating player wins.

### The Game Board

The game board is an 8 × 8 grid. The middle two squares on the first and last rows are server ports. Players set up their links on their respective rows, avoiding server ports. Here are examples of board setups:

``` Player 1:
Downloaded: 0D, 0V
Abilities: 5
a: V1 b: D4 c: V3 d: V2
e: D3 f: V4 g: D2 h: D1
========
abcSSfgh
...de...
........
........
........
........
...DE...
ABCSSFGH
========
Player 2:
Downloaded: 0D, 0V
Abilities: 5
A: ? B: ? C: ? D: ?
E: ? F: ? G: ? H: ?


Player 1:
Downloaded: 1D, 2V
Abilities: 3
a: V1 b: D4 c: V3 d: V2
e: D3 f: V4 g: D2 h: D1
========
a.cSSf.h
...E..g.
........
........
........
A.......
...D.F..
...SS.GH
========
Player 2:
Downloaded: 1D, 1V
Abilities: 3
A: ? B: V2 C: V3 D: ?
E: V4 F: ? G: ? H: ?
```


### Abilities

Players have five types of ability cards at the start of the game, which can each be used once:
1. Link Boost: Increases the movement range of a link.
2. Firewall: Reveals and potentially downloads opposing links passing through a targeted square.
3. Download: Immediately downloads a targeted link.
4. Polarize: Converts a data link to a virus or vice versa.
5. Scan: Reveals the type and strength of a targeted link.

There are three more abilities named after Stands in JOJO: KingCrimson, MadeInHeaven, TheWorld. Try explore their abilities yourself!

### Commands

Players interact with the game using the following commands:
- `move <link> <direction>`: Moves the specified link in the given direction (up, down, left, right).
- `abilities`: Displays available ability cards.
- `ability <ID>`: Uses the specified ability card.
- `board`: Displays the current game board.
- `sequence <file>`: Executes commands from a file.
- `quit`: Exits the game.

### Command Line Options

- `-ability1 <order>`: Sets abilities for player 1.
- `-ability2 <order>`: Sets abilities for player 2.
- `-link1 <placement-file>`: Specifies initial link placements for player 1.
- `-link2 <placement-file>`: Specifies initial link placements for player 2.
- `-graphics`: Enables the graphical interface.

### Winning and Losing

The game ends when a player achieves either of the following:
- Downloads four data (wins).
- Downloads four viruses (loses).

The game outputs the winner and stops when the game ends.
