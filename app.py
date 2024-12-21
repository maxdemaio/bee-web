from flask import Flask, render_template, request, jsonify
import struct

app = Flask(__name__)

def negate_binary(binary):
    return ~binary & 0xFFFFFFFF  # Flip bits and mask to 32-bit

def string_to_binary(word):
    binary = 0
    for char in word.lower():  # Convert to lowercase to handle case insensitivity
        if 'a' <= char <= 'z':  # Ensure it's a valid alphabet letter
            position = ord(char) - ord('a')  # Calculate the position of the letter (0-25)
            binary |= (1 << position)  # Flip the bit at the calculated position
    # Bitwise not operation to create the solution cypher
    return binary

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/solve", methods=["POST"])
def solve_puzzle():
    letters = request.form["letters"].lower()
    required_letter = request.form["required_letter"].lower()
    print(letters)
    print(required_letter)

    if len(letters) != 6 or not required_letter.isalpha() or len(required_letter) != 1:
        return jsonify({"error": "Invalid input"}), 400

    words = ["cats", "blogs", "frick"]
    pangram = "ayo"

    # Example usage
    word = "cats"
    binary_representation = string_to_binary(word)
    cypher = negate_binary(binary_representation)

    # Format as a 32-bit binary string
    binary_string = f"{cypher:032b}"
    print(f"Word: {word}")
    print(f"Binary (32-bit): {binary_string}")

    return jsonify({"words": words, "pangram": pangram})

if __name__ == "__main__":
    app.run(port=8000, debug=True)