#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ===========================================================
   SISTEM PERINGKAT NILAI MAHASISWA: BST & AVL DALAM 1 PROGRAM
   - Kunci unik: nilai (int)
   - Node menyimpan (nama, nilai) + height (untuk AVL)
   - Semua operasi (insert/delete) pakai isAVL untuk toggle AVL
   =========================================================== */

#define NAME_MAXLEN 50

typedef struct {
    int  nilai;                 // kunci unik
    char nama[NAME_MAXLEN + 1]; // nama mahasiswa
} Mahasiswa;

typedef struct Node {
    Mahasiswa mhs;
    int height;                 // tinggi versi AVL (leaf = 1)
    struct Node *left, *right;
} Node;

/* ---------- Util I/O ---------- */
static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n && s[n-1] == '\n') s[n-1] = '\0';
}
static void flush_stdin(void) {
    int c; while ((c=getchar())!='\n' && c!=EOF);
}
static void input_line(char *buf, size_t cap) {
    if (fgets(buf, (int)cap, stdin) == NULL) { buf[0]='\0'; return; }
    trim_newline(buf);
}

/* ---------- Node helpers ---------- */
static Node* new_node(const char *nama, int nilai) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->mhs.nilai = nilai;
    strncpy(n->mhs.nama, nama, NAME_MAXLEN);
    n->mhs.nama[NAME_MAXLEN] = '\0';
    n->left = n->right = NULL;
    n->height = 1; // definisi AVL: leaf = 1
    return n;
}

static int h(Node *n) { return n ? n->height : 0; }
static int max2(int a, int b) { return a>b ? a : b; }
static int bf(Node *n) { return n ? h(n->left) - h(n->right) : 0; }

/* ---------- Rotations (AVL) ---------- */
static Node* rightRotate(Node *y) {
    Node *x  = y->left;
    Node *T2 = x->right;
    // rotate
    x->right = y;
    y->left  = T2;
    // update height
    y->height = 1 + max2(h(y->left), h(y->right));
    x->height = 1 + max2(h(x->left), h(x->right));
    return x;
}
static Node* leftRotate(Node *x) {
    Node *y  = x->right;
    Node *T2 = y->left;
    // rotate
    y->left  = x;
    x->right = T2;
    // update height
    x->height = 1 + max2(h(x->left), h(x->right));
    y->height = 1 + max2(h(y->left), h(y->right));
    return y;
}

/* ---------- Search ---------- */
static Node* search_bst(Node *root, int nilai) {
    if (!root || root->mhs.nilai == nilai) return root;
    if (nilai < root->mhs.nilai) return search_bst(root->left, nilai);
    else                         return search_bst(root->right, nilai);
}

/* ---------- Insert (BST core + optional AVL rebalance) ---------- */
static Node* insert_core(Node *root, const char *nama, int nilai, int isAVL, int *inserted) {
    if (!root) {
        *inserted = 1;
        return new_node(nama, nilai);
    }
    if (nilai < root->mhs.nilai) {
        root->left  = insert_core(root->left, nama, nilai, isAVL, inserted);
    } else if (nilai > root->mhs.nilai) {
        root->right = insert_core(root->right, nama, nilai, isAVL, inserted);
    } else {
        // duplikat - tolak
        *inserted = 0;
        return root;
    }

    if (!isAVL) return root;

    // update height + rebalance
    root->height = 1 + max2(h(root->left), h(root->right));
    int balance = bf(root);

    // LL
    if (balance > 1 && nilai < root->left->mhs.nilai)
        return rightRotate(root);
    // RR
    if (balance < -1 && nilai > root->right->mhs.nilai)
        return leftRotate(root);
    // LR
    if (balance > 1 && nilai > root->left->mhs.nilai) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RL
    if (balance < -1 && nilai < root->right->mhs.nilai) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

/* ---------- Min node (untuk delete 2 anak) ---------- */
static Node* min_node(Node *root) {
    Node *cur = root;
    while (cur && cur->left) cur = cur->left;
    return cur;
}

/* ---------- Delete (BST core + optional AVL rebalance) ---------- */
static Node* delete_core(Node *root, int nilai, int isAVL, int *deleted) {
    if (!root) return NULL;

    if (nilai < root->mhs.nilai) {
        root->left = delete_core(root->left, nilai, isAVL, deleted);
    } else if (nilai > root->mhs.nilai) {
        root->right = delete_core(root->right, nilai, isAVL, deleted);
    } else {
        // found
        *deleted = 1;
        // 0 atau 1 anak
        if (!root->left || !root->right) {
            Node *child = root->left ? root->left : root->right;
            free(root);
            return child;
        }
        // 2 anak: pakai inorder successor
        Node *succ = min_node(root->right);
        root->mhs = succ->mhs; // salin nama & nilai
        root->right = delete_core(root->right, succ->mhs.nilai, isAVL, deleted);
    }

    if (!isAVL || !root) return root;

    // update height + rebalance
    root->height = 1 + max2(h(root->left), h(root->right));
    int balance = bf(root);

    // LL
    if (balance > 1 && bf(root->left) >= 0)
        return rightRotate(root);
    // LR
    if (balance > 1 && bf(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RR
    if (balance < -1 && bf(root->right) <= 0)
        return leftRotate(root);
    // RL
    if (balance < -1 && bf(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

/* ---------- Traversal & Tabel ---------- */
static void print_table_header(void) {
    printf("+-------+----------------------------------+\n");
    printf("| Nilai | Nama                             |\n");
    printf("+-------+----------------------------------+\n");
}
static void print_table_row(const Node *n) {
    printf("| %5d | %-32s |\n", n->mhs.nilai, n->mhs.nama);
}
static void print_table_footer(void) {
    printf("+-------+----------------------------------+\n");
}
static void inorder_table(Node *root) {
    if (!root) return;
    inorder_table(root->left);
    print_table_row(root);
    inorder_table(root->right);
}

/* ---------- Statistik ---------- */
static int count_nodes(Node *root) {
    if (!root) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}
static int count_leaves(Node *root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return count_leaves(root->left) + count_leaves(root->right);
}
// Height untuk laporan (berbasis edge): NULL = -1, leaf = 0
static int height_edges(Node *root) {
    if (!root) return -1;
    int hl = height_edges(root->left);
    int hr = height_edges(root->right);
    return (hl>hr?hl:hr) + 1;
}

/* ---------- Clear ---------- */
static void clear_tree(Node *root) {
    if (!root) return;
    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}

/* ---------- Seed data contoh ---------- */
static Node* seed_sample(Node *root, int isAVL) {
    struct { const char *nama; int nilai; } sampel[] = {
        {"Andi", 75}, {"Budi", 60}, {"Citra", 80}, {"Deni", 65}, {"Ema", 70},
        {"Fajar", 85}, {"Gita", 90}, {"Hani", 72}, {"Ivan", 68}
    };
    for (size_t i=0;i<sizeof(sampel)/sizeof(sampel[0]);++i) {
        int inserted = 0;
        root = insert_core(root, sampel[i].nama, sampel[i].nilai, isAVL, &inserted);
    }
    return root;
}

/* ---------- Menu umum ---------- */
static void pause_enter(void) {
    printf("\n(Enter untuk lanjut) ");
    fflush(stdout);
    int c; while ((c=getchar())!='\n' && c!=EOF);
}

static void print_stats(Node *root) {
    printf("Size  : %d\n", count_nodes(root));
    printf("Leaf  : %d\n", count_leaves(root));
    printf("Height (edges): %d\n", height_edges(root));
}

/* ---------- Menu BST/AVL (berbagi kode) ---------- */
static void tree_menu(int isAVL) {
    Node *root = NULL;
    int pilih;
    for (;;) {
        printf("\n===== %s MENU =====\n", isAVL ? "AVL" : "BST");
        printf("1. Insert data\n");
        printf("2. Search data (berdasarkan nilai)\n");
        printf("3. Delete data (berdasarkan nilai)\n");
        printf("4. Tampilkan (Inorder - terurut)\n");
        printf("5. Statistik (size/leaf/height)\n");
        printf("6. Seed data contoh\n");
        printf("7. Clear tree\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        if (scanf("%d", &pilih)!=1) { puts("Input tidak valid."); return; }
        flush_stdin();

        if (pilih == 0) { clear_tree(root); return; }

        if (pilih == 1) {
            char nama[NAME_MAXLEN+1];
            int nilai;
            printf("Nama  : "); input_line(nama, sizeof(nama));
            if (nama[0]=='\0') { puts("Nama tidak boleh kosong."); continue; }
            printf("Nilai : ");
            if (scanf("%d", &nilai)!=1) { puts("Nilai tidak valid."); flush_stdin(); continue; }
            flush_stdin();

            int inserted = 0;
            root = insert_core(root, nama, nilai, isAVL, &inserted);
            if (inserted) puts("-> Data berhasil ditambahkan.");
            else          puts("-> Duplikat nilai: data ditolak.");
            pause_enter();

        } else if (pilih == 2) {
            if (!root) { puts("Tree kosong."); pause_enter(); continue; }
            int nilai;
            printf("Nilai dicari: ");
            if (scanf("%d", &nilai)!=1) { puts("Nilai tidak valid."); flush_stdin(); continue; }
            flush_stdin();
            Node *f = search_bst(root, nilai);
            if (f) {
                print_table_header();
                print_table_row(f);
                print_table_footer();
            } else puts("-> Tidak ditemukan.");
            pause_enter();

        } else if (pilih == 3) {
            if (!root) { puts("Tree kosong."); pause_enter(); continue; }
            int nilai, deleted=0;
            printf("Nilai dihapus: ");
            if (scanf("%d", &nilai)!=1) { puts("Nilai tidak valid."); flush_stdin(); continue; }
            flush_stdin();
            root = delete_core(root, nilai, isAVL, &deleted);
            if (deleted) puts("-> Data berhasil dihapus.");
            else         puts("-> Data tidak ditemukan.");
            pause_enter();

        } else if (pilih == 4) {
            if (!root) { puts("Tree kosong."); pause_enter(); continue; }
            print_table_header();
            inorder_table(root);
            print_table_footer();
            pause_enter();

        } else if (pilih == 5) {
            print_stats(root);
            pause_enter();

        } else if (pilih == 6) {
            root = seed_sample(root, isAVL);
            puts("-> Seed data contoh ditambahkan.");
            pause_enter();

        } else if (pilih == 7) {
            clear_tree(root); root = NULL;
            puts("-> Tree dikosongkan.");
            pause_enter();

        } else {
            puts("Menu tidak tersedia.");
        }
    }
}

/* ---------- Main: pilih BST atau AVL ---------- */
int main(void) {
    for (;;) {
        int pilih;
        printf("\n========= MAIN MENU =========\n");
        printf("1. Mode BST (tanpa rebalance)\n");
        printf("2. Mode AVL (auto rebalance)\n");
        printf("0. Keluar\n");
        printf("Pilih: ");
        if (scanf("%d", &pilih)!=1) { puts("Input tidak valid."); break; }
        flush_stdin();

        if (pilih == 0) break;
        else if (pilih == 1) tree_menu(0); // BST
        else if (pilih == 2) tree_menu(1); // AVL
        else puts("Menu tidak tersedia.");
    }
    puts("Terima kasih. Program selesai.");
    return 0;
}