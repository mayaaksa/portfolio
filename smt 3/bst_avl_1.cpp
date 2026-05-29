#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

/* ================= NODE ================= */
struct Node {
    int npm;
    string nama, prodi;
    int semester;
    Node *left, *right;
    int height; // dipakai AVL

    Node(int n, string nm, string pr, int smt) {
        npm = n;
        nama = nm;
        prodi = pr;
        semester = smt;
        left = right = NULL;
        height = 1;
    }
};

/* ================= UTIL ================= */
int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* node) { // untuk balancing AVL
    return node ? node->height : 0;
}

int hitungHeight(Node* root) { // untuk laporan
    if (root == NULL)
        return 0;

    return 1 + max(hitungHeight(root->left),
                   hitungHeight(root->right));
}

int countNode(Node* root) {
    if (!root) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int countLeaf(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

/* ================= TRAVERSAL ================= */
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->npm << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->npm << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->npm << " ";
}

/* ================= BST ================= */
Node* insertBST(Node* root, Node* newNode) {
    if (!root) return newNode;

    if (newNode->npm < root->npm)
        root->left = insertBST(root->left, newNode);
    else if (newNode->npm > root->npm)
        root->right = insertBST(root->right, newNode);
    else
        cout << "NPM sudah ada!\n";

    return root;
}

Node* search(Node* root, int npm) {
    if (!root || root->npm == npm) return root;
    if (npm < root->npm) return search(root->left, npm);
    return search(root->right, npm);
}

Node* minValue(Node* node) {
    while (node->left) node = node->left;
    return node;
}

Node* deleteNode(Node* root, int npm) {
    if (!root) return root;

    if (npm < root->npm)
        root->left = deleteNode(root->left, npm);
    else if (npm > root->npm)
        root->right = deleteNode(root->right, npm);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValue(root->right);
        root->npm = temp->npm;
        root->nama = temp->nama;
        root->prodi = temp->prodi;
        root->semester = temp->semester;
        root->right = deleteNode(root->right, temp->npm);
    }
    return root;
}

/* ================= AVL ================= */
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

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

Node* insertAVL(Node* root, Node* newNode) {
    if (!root) return newNode;

    if (newNode->npm < root->npm)
        root->left = insertAVL(root->left, newNode);
    else if (newNode->npm > root->npm)
        root->right = insertAVL(root->right, newNode);
    else {
        cout << "⚠️ NPM sudah ada!\n";
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    // LL
    if (balance > 1 && newNode->npm < root->left->npm)
        return rightRotate(root);

    // RR
    if (balance < -1 && newNode->npm > root->right->npm)
        return leftRotate(root);

    // LR
    if (balance > 1 && newNode->npm > root->left->npm) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && newNode->npm < root->right->npm) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* ================= DISPLAY ================= */
void tampilHeader() {
    cout << left
         << setw(6)  << "NPM"
         << setw(20) << "Nama"
         << setw(22) << "Prodi"
         << setw(10) << "Semester" << endl;

    cout << string(58, '-') << endl;
}

void tampilIsi(Node* root) {
    if (!root) return;

    tampilIsi(root->left);

    cout << left
         << setw(6)  << root->npm
         << setw(20) << root->nama
         << setw(22) << root->prodi
         << setw(10) << root->semester << endl;

    tampilIsi(root->right);
}

void tampilData(Node* root) {
    if (root == NULL) {
        cout << "Data masih kosong!\n";
        return;
    }

    cout << "\n=========== DATA MAHASISWA ===========\n";
    tampilHeader();
    tampilIsi(root);
    cout << string(58, '=') << endl;
}

/* ================= DUMMY DATA ================= */
void insertDummy(Node*& root, bool avl) {
    int npm[10] = {218, 221, 340, 111, 145, 290, 410, 333, 199, 256};

    string nama[10] = {
        "Zuyyina Aaliyah",
        "Maya Aksa",
        "Citra Lestari",
        "Dewi Anggraini",
        "Eka Saputra",
        "Fajar Nugroho",
        "Gita Maharani",
        "Hendra Wijaya",
        "Intan Permata",
        "Joko Firmansyah"
    };

    string prodi[10] = {
        "Informatika",
        "Informatiika",
        "Hukum",
        "Manajemen",
        "Sains Data",
        "Sistem Informasi",
        "Ilmu Komunikasi",
        "Hukum",
        "Informatika",
        "Sistem Informasi"
    };

    int semester[10] = {2, 4, 6, 2, 8, 4, 6, 2, 8, 4};

    for (int i = 0; i < 10; i++) {
        Node* n = new Node(
            npm[i],
            nama[i],
            prodi[i],
            semester[i]
        );

        root = avl ? insertAVL(root, n) : insertBST(root, n);
    }

    cout << "Dummy data berhasil ditambahkan!\n";
}

/* ================= EXPORT TO .TXT ================= */
void exportData(Node* root, ofstream& file) {
    if (!root) return;

    exportData(root->left, file);

    file << root->npm << "\t"
         << root->nama << "\t"
         << root->prodi << "\t"
         << root->semester << endl;

    exportData(root->right, file);
}

void exportInorder(Node* root, ofstream& file) {
    if (!root) return;
    exportInorder(root->left, file);
    file << root->npm << " ";
    exportInorder(root->right, file);
}

void exportPreorder(Node* root, ofstream& file) {
    if (!root) return;
    file << root->npm << " ";
    exportPreorder(root->left, file);
    exportPreorder(root->right, file);
}

void exportPostorder(Node* root, ofstream& file) {
    if (!root) return;
    exportPostorder(root->left, file);
    exportPostorder(root->right, file);
    file << root->npm << " ";
}

void exportToTxt(Node* root, bool avl) {
    if (root == NULL) {
        cout << "Data masih kosong, tidak ada yang bisa diexport!\n";
        return;
    }

    string filename;
    cout << "Masukkan nama file (.txt): ";
    cin >> filename;

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuat file!\n";
        return;
    }

    file << "===== EXPORT DATA KRS MAHASISWA =====\n";
    file << "Jenis Tree : " << (avl ? "AVL Tree" : "Binary Search Tree") << "\n\n";

    /* DATA MAHASISWA */
    file << "=== DATA MAHASISWA (Inorder / Terurut NPM) ===\n";
    file << "NPM\tNama\tProdi\tSemester\n";
    file << "-------------------------------------------\n";
    exportData(root, file);

    /* STATISTIK */
    file << "\n=== STATISTIK TREE ===\n";
    file << "Size   : " << countNode(root) << endl;
    cout << "Height : " << hitungHeight(root) << endl;
    file << "Leaf   : " << countLeaf(root) << endl;

    /* TRAVERSAL */
    file << "\n=== TRAVERSAL TREE ===\n";

    file << "Inorder   : ";
    exportInorder(root, file);
    file << endl;

    file << "Preorder  : ";
    exportPreorder(root, file);
    file << endl;

    file << "Postorder : ";
    exportPostorder(root, file);
    file << endl;

    file.close();
    cout << "Data berhasil diexport ke file " << filename << endl;
}

/* ================= MENU ================= */
void menuTree(bool avl) {
    Node* root = NULL;
    int pilih;

do {
    cout << "\n=== Menu " << (avl ? "AVL" : "BST") << " ===\n";
    cout << "1. Dummy Data\n";
    cout << "2. Insert Data Mahasiswa\n";
    cout << "3. Tampilkan Data Mahasiswa\n";
    cout << "4. Cari Data Mahasiswa\n";
    cout << "5. Delete Data Mahasiswa\n";
    cout << "6. Statistik & Traversal\n";
    cout << "7. Clear Data\n";
    cout << "8. Kembali ke Menu Utama\n";
    cout << "9. Export to .txt\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
    cin >> pilih;

    switch (pilih) {

    case 1:
        insertDummy(root, avl);
        break;

    case 2: {
        int npm, smt;
        string nama, prodi;
        cout << "NPM (3 digit): ";
        cin >> npm;
        cin.ignore();
        cout << "Nama     : ";
        getline(cin, nama);
        cout << "Prodi    : ";
        getline(cin, prodi);
        cout << "Semester : ";
        cin >> smt;

        Node* n = new Node(npm, nama, prodi, smt);
        root = avl ? insertAVL(root, n) : insertBST(root, n);
        break;
    }

    case 3:
        if (root == NULL) {
            cout << "Data masih kosong!\n";
        } else {
            cout << "\n=== Data Mahasiswa ===\n";
            tampilData(root);
        }
        break;

    case 4: {
        if (root == NULL) {
            cout << "Data masih kosong!\n";
        } else {
            int npm;
            cout << "Cari NPM: ";
            cin >> npm;

            Node* res = search(root, npm);
            if (res) {
                cout << "Data ditemukan\n";
                cout << "Nama     : " << res->nama << endl;
                cout << "Prodi    : " << res->prodi << endl;
                cout << "Semester : " << res->semester << endl;
            } else {
                cout << "Data tidak ditemukan\n";
            }
        }
        break;
    }

    case 5: {
        if (root == NULL) {
            cout << "Data masih kosong!\n";
        } else {
            int npm;
            cout << "Hapus NPM: ";
            cin >> npm;
            root = deleteNode(root, npm);
            cout << "Data berhasil diproses\n";
        }
        break;
    }

    case 6:
        if (root == NULL) {
            cout << "Data masih kosong!\n";
        } else {
            cout << "\n=== Statistik Tree ===\n";
            cout << "Size   : " << countNode(root) << endl;
            cout << "Height : " << hitungHeight(root) << endl;
            cout << "Leaf   : " << countLeaf(root) << endl;

            cout << "Inorder   : ";
            inorder(root); cout << endl;

            cout << "Preorder  : ";
            preorder(root); cout << endl;

            cout << "Postorder : ";
            postorder(root); cout << endl;
        }
        break;

    case 7:
        root = NULL;
        cout << "Data berhasil dihapus semua\n";
        break;
    case 8:
        cout << "Kembali ke Menu Utama\n";
        break;
    case 9:
        exportToTxt(root, avl);
    break;
    case 0:
        cout << "Program selesai\n";
        break;
    default:
        cout << "Pilihan tidak valid\n";
    }

} while (pilih != 0 && pilih != 8);
}

/* ================= MAIN ================= */
int main() {
    int pilih;
do {
    cout << "\n=== MENU UTAMA ===\n";
    cout << "1. BST\n";
    cout << "2. AVL\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
    cin >> pilih;

    switch (pilih) {
    case 1:
        menuTree(false);
        break;
    case 2:
        menuTree(true);
        break;
    case 0:
        cout << "Program selesai\n";
        break;
    default:
        cout << "Pilihan tidak valid\n";
    }
} while (pilih != 0);

    return 0;
}