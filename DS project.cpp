#include <iostream>
#include <string>
using namespace std;

// ------------------ NODE STRUCTURE ------------------
struct Node {
    string word;
    string meaning;
    Node* left;
    Node* right;
    int height;
    Node(string w, string m) {
        word = w;
        meaning = m;
        left = right = NULL;
        height = 1;
    }
};

// Utility
int getHeight(Node* n) { return n ? n->height : 0; }

int getBalance(Node* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

int max(int a, int b) { return (a > b) ? a : b; }

// ------------------ ROTATIONS ------------------
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// ------------------ INSERT ------------------
Node* insert(Node* root, string key, string meaning) {
    if (!root)
        return new Node(key, meaning);

    if (key < root->word)
        root->left = insert(root->left, key, meaning);
    else if (key > root->word)
        root->right = insert(root->right, key, meaning);
    else
        return root;  // duplicates not allowed

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    // LL
    if (balance > 1 && key < root->left->word)
        return rightRotate(root);

    // RR
    if (balance < -1 && key > root->right->word)
        return leftRotate(root);

    // LR
    if (balance > 1 && key > root->left->word) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && key < root->right->word) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// -------------------------------------------------------
// ?? PREFIX SEARCH (WORD + MEANING)
// -------------------------------------------------------
void searchPrefix(Node* root, string prefix) {
    if (!root) return;

    searchPrefix(root->left, prefix);

    if (root->word.rfind(prefix, 0) == 0) {
        cout << " ? " << root->word << " = " << root->meaning << endl;
    }

    searchPrefix(root->right, prefix);
}

void search(Node* root, string prefix) {
    cout << "\nWords starting with '" << prefix << "' :\n";
    cout << "-----------------------------------\n";
    searchPrefix(root, prefix);
    cout << "-----------------------------------\n";
}

// ------------------ LOAD DEFAULT WORDS + MEANINGS ------------------
Node* loadDefault(Node* root) {

    // 26 letters × 5 words each with meanings
    string words[26][5] = {
        {"apple","ant","arrow","area","age"},
        {"ball","bat","bag","barn","bank"},
        {"cat","car","cup","cow","cake"},
        {"dog","door","dance","disk","dust"},
        {"egg","ear","east","eye","engine"},
        {"fish","fan","farm","fear","file"},
        {"goat","gun","game","gate","glass"},
        {"hat","hen","hill","horse","house"},
        {"ice","iron","idea","item","ink"},
        {"jug","jam","job","jungle","jeep"},
        {"kite","king","kid","knot","knee"},
        {"lion","leg","lip","log","leaf"},
        {"man","map","mouse","milk","moon"},
        {"nose","net","nail","neck","nest"},
        {"orange","oil","oven","ox","one"},
        {"pen","pin","pig","pot","pan"},
        {"queen","quick","quit","quiz","quote"},
        {"rat","rain","ring","rope","road"},
        {"sun","sit","sand","ship","shoe"},
        {"tap","top","toy","tank","time"},
        {"umbrella","unit","use","undo","up"},
        {"van","vase","vine","vote","voice"},
        {"water","wax","wall","well","wing"},
        {"xray","xerox","xenon","xmas","xylem"},
        {"yak","yarn","yard","yellow","youth"},
        {"zoo","zap","zero","zone","zebra"}
    };

    string meanings[26][5] = {
        {"a fruit","a small insect","a pointed weapon","a place","years lived"},
        {"a round object","a hitting stick","a container","farm building","money place"},
        {"a pet animal","a vehicle","a drinking cup","a farm animal","a sweet dessert"},
        {"a pet animal","entry/exit","movement","storage device","tiny particles"},
        {"food from birds","hearing organ","direction","vision organ","machine part"},
        {"water animal","cooling device","land area","scared feeling","stored data"},
        {"farm animal","weapon","activity","entry gate","transparent material"},
        {"headwear","female chicken","small hill","big animal","living place"},
        {"frozen water","metal","thought","object","writing ink"},
        {"water container","fruit paste","work task","forest","vehicle"},
        {"flying toy","male ruler","child","rope tie","leg joint"},
        {"wild animal","body part","mouth part","wood piece","tree part"},
        {"adult male","location drawing","small animal","white drink","night object"},
        {"smell organ","netting","metal pin","body part","bird home"},
        {"citrus fruit","liquid fat","kitchen device","animal","number"},
        {"writing tool","sharp object","farm animal","cooking pot","flat pan"},
        {"female ruler","fast","stop","test","repeat words"},
        {"small animal","water drops","circular band","strong rope","path"},
        {"day star","to sit","tiny stones","sea vehicle","footwear"},
        {"water tap","high point","plaything","army vehicle","clock time"},
        {"rain cover","single piece","to use","reverse action","higher position"},
        {"vehicle","flower pot","plant branch","election choice","sound"},
        {"drink liquid","wax material","wall surface","good","bird wing"},
        {"body scan","copy machine","chemical","christmas","plant tissue"},
        {"Tibetan ox","thread ball","house area","color","young person"},
        {"animal place","electric sound","nothing","area","striped animal"}
    };

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            root = insert(root, words[i][j], meanings[i][j]);

    return root;
}

// ------------------ MAIN ------------------
int main() {
    Node* root = NULL;
    root = loadDefault(root);

    cout << "Dictionary Loaded Successfully with Meanings!\n";

    while (true) {
        cout << "\n1. Insert Word";
        cout << "\n2. Search ";
        cout << "\n3. Exit";
        cout << "\nEnter choice: ";
        int ch;
        cin >> ch;

        if (ch == 1) {
            string w, m;
            cout << "Enter word: ";
            cin >> w;
            cout << "Enter meaning: ";
            cin.ignore();
            getline(cin, m);
            root = insert(root, w, m);
            cout << "Word inserted!\n";
        }
        else if (ch == 2) {
            string p;
            cout << "Enter word/prefix to search: ";
            cin >> p;
            search(root, p);
        }
        else if (ch == 3) break;
        else cout << "Invalid choice!\n";
    }

    return 0;
}
