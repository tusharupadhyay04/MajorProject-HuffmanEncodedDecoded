#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

// Node structure
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Comparison class for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffCode) {
    if (root == nullptr) return;

    if (root->left == nullptr && root->right == nullptr) {
        huffCode[root->ch] = code;
        return;
    }

    generateCodes(root->left, code + "0", huffCode);
    generateCodes(root->right, code + "1", huffCode);
}

// Encode the input text
string encode(string text, unordered_map<char, string>& huffCode) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        result += huffCode[text[i]];
    }
    return result;
}

// Decode the encoded binary string
string decode(string binary, Node* root) {
    string result = "";
    Node* current = root;

    for (int i = 0; i < binary.length(); i++) {
        if (binary[i] == '0') current = current->left;
        else current = current->right;

        if (current->left == nullptr && current->right == nullptr) {
            result += current->ch;
            current = root;
        }
    }

    return result;
}

// Main function
int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    // Count frequency
    unordered_map<char, int> freq;
    for (int i = 0; i < text.length(); i++) {
        freq[text[i]]++;
    }

    // Create min-heap
    priority_queue<Node*, vector<Node*>, Compare> pq;
    unordered_map<char, int>::iterator it;
    for (it = freq.begin(); it != freq.end(); ++it) {
        pq.push(new Node(it->first, it->second));
    }

    // Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();

    // Generate codes
    unordered_map<char, string> huffCode;
    generateCodes(root, "", huffCode);

    // Print codes
    cout << "\nHuffman Codes:\n";
    unordered_map<char, string>::iterator it2;
    for (it2 = huffCode.begin(); it2 != huffCode.end(); ++it2) {
        cout << it2->first << ": " << it2->second << endl;
    }

    // Encode
    string encoded = encode(text, huffCode);
    cout << "\nEncoded String:\n" << encoded << endl;

    // Decode
    string decoded = decode(encoded, root);
    cout << "\nDecoded String:\n" << decoded << endl;

    return 0;
}
