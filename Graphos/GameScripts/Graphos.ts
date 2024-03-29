// Interface for Vectors
class Vector3
{
    public x: Number;
    public y: Number;
    public z: Number;
}

// Interface for object transforms
class Transform
{
    public position: Vector3;
    public rotation: Vector3;
    public scale: Vector3;
}

// Class with variables and functions
class GameObject
{
    // ID of owner object
    public id: string;

    // Transform object
    public transform: Transform;

    // Abstract method for updating object
    public Update( deltaTime: number ): void
    {
        throw new Error( "Implement your own damn Update!" );
    }
}

// Interface that allows GameObjects to check for input
interface Input
{
    IsKeyDown( key: number ): bool;
}
declare var Input: Input;

// Print function
declare function log(toPrint: any): void;

// Include function
declare function include(path: string): void;

var Keys = {
    "backspace": 8,
    "tab": 9,
    "return": 13,
    "shift": 16,
    "ctrl": 17,
    "alt": 18,
    "pausebreak": 19,
    "capslock": 20,
    "escape": 27,
    "space": 32,
    "pageup": 33,
    "pagedown": 34,
    "end": 35,
    "home": 36,
    "left": 37,
    "up": 38,
    "right": 39,
    "down": 40,
    "+": 43,
    "printscreen": 44,
    "insert": 45,
    "delete": 46,
    "0": 48,
    "1": 49,
    "2": 50,
    "3": 51,
    "4": 52,
    "5": 53,
    "6": 54,
    "7": 55,
    "8": 56,
    "9": 57,
    ";": 59,
    "=": 61,
    "a": 65,
    "b": 66,
    "c": 67,
    "d": 68,
    "e": 69,
    "f": 70,
    "g": 71,
    "h": 72,
    "i": 73,
    "j": 74,
    "k": 75,
    "l": 76,
    "m": 77,
    "n": 78,
    "o": 79,
    "p": 80,
    "q": 81,
    "r": 82,
    "s": 83,
    "t": 84,
    "u": 85,
    "v": 86,
    "w": 87,
    "x": 88,
    "y": 89,
    "z": 90,
    "numpad 0": 96,
    "numpad 1": 97,
    "numpad 2": 98,
    "numpad 3": 99,
    "numpad 4": 100,
    "numpad 5": 101,
    "numpad 6": 102,
    "numpad 7": 103,
    "numpad 8": 104,
    "numpad 9": 105,
    "numpad *": 106,
    "numpad +": 107,
    "numpad -": 109,
    "numpad .": 110,
    "numpad /": 111,
    "f1": 112,
    "f2": 113,
    "f3": 114,
    "f4": 115,
    "f5": 116,
    "f6": 117,
    "f7": 118,
    "f8": 119,
    "f9": 120,
    "f10": 121,
    "f11": 122,
    "f12": 123,
    "numlock": 144,
    "scrolllock": 145,
    ";": 186,
    "=": 187,
    ",": 188,
    "-": 189,
    ".": 190,
    "/": 191,
    "`": 192,
    "[": 219,
    "\\": 220,
    "]": 221,
    "'": 222
}