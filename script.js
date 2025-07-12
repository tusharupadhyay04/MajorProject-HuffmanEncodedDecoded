let huffmanTree = null;

class Node {
  constructor(char, freq, left = null, right = null) {
    this.char = char;
    this.freq = freq;
    this.left = left;
    this.right = right;
  }
}

// Generate frequency map
function buildFrequencyMap(text) {
  const freqMap = {};
  for (let char of text) {
    freqMap[char] = (freqMap[char] || 0) + 1;
  }
  return freqMap;
}

// Build Huffman tree
function buildHuffmanTree(freqMap) {
  const nodes = Object.entries(freqMap).map(([char, freq]) => new Node(char, freq));
  
  while (nodes.length > 1) {
    nodes.sort((a, b) => a.freq - b.freq);
    const left = nodes.shift();
    const right = nodes.shift();
    const newNode = new Node(null, left.freq + right.freq, left, right);
    nodes.push(newNode);
  }

  return nodes[0];
}

// Generate codes
function generateCodes(node, path = "", codeMap = {}) {
  if (!node) return;

  if (node.char !== null) {
    codeMap[node.char] = path;
  }

  generateCodes(node.left, path + "0", codeMap);
  generateCodes(node.right, path + "1", codeMap);

  return codeMap;
}

// It Compress the text we have given
function compressText() {
  const input = document.getElementById("inputText").value;
  if (!input) {
    alert("Please enter some text.");
    return;
  }

  const freqMap = buildFrequencyMap(input);
  huffmanTree = buildHuffmanTree(freqMap);
  const codes = generateCodes(huffmanTree);

  let encoded = "";
  for (let char of input) {
    encoded += codes[char];
  }

  document.getElementById("encodedOutput").innerText = encoded;
  document.getElementById("decodedOutput").innerText = "";
}

// It Decompress text the encoded text we have given
function decompressText() {
  const binary = document.getElementById("encodedOutput").innerText;
  if (!binary || !huffmanTree) {
    alert("Please compress some text first.");
    return;
  }

  let result = "";
  let current = huffmanTree;

  for (let bit of binary) {
    current = bit === '0' ? current.left : current.right;

    if (current.char !== null) {
      result += current.char;
      current = huffmanTree;
    }
  }

  document.getElementById("decodedOutput").innerText = result;
}
// It Reset all the text and output
function resetAll() {
  document.getElementById("inputText").value = "";
  document.getElementById("encodedOutput").innerText = "";
  document.getElementById("decodedOutput").innerText = "";
  huffmanTree = null;
}
