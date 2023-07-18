#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha.h"
#include "filters.h"
#include "hex.h"

#define MAX_DATA_LENGTH 256

using namespace CryptoPP;

// Merkle Tree 节点结构体
typedef struct MerkleTreeNode {
    char data[MAX_DATA_LENGTH];     // 节点数据
    char hash[CryptoPP::SHA256::DIGESTSIZE * 2 + 1];    // 节点哈希值
    struct MerkleTreeNode* left;    // 左子节点指针
    struct MerkleTreeNode* right;   // 右子节点指针
} MerkleTreeNode;

// Merkle Tree 结构体
typedef struct MerkleTree {
    struct MerkleTreeNode* root;    // 根节点指针
} MerkleTree;

// 计算 SHA256 哈希值
void CalculateSHA256(const char* data, char* hash)
{
    std::string input(data);
    std::string digest;

    CryptoPP::SHA256 hashFunction;
    hashFunction.Update(reinterpret_cast<const unsigned char*>(input.data()), input.size());
    digest.resize(hashFunction.DigestSize());
    hashFunction.Final(reinterpret_cast<unsigned char*>(&digest[0]));

    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::ArraySink(reinterpret_cast<unsigned char*>(hash), hashFunction.DigestSize()));
    encoder.Put(reinterpret_cast<const unsigned char*>(digest.data()), digest.size());
    encoder.MessageEnd();
}

// 创建 Merkle Tree
MerkleTree* CreateMerkleTree(char* leaves[], size_t numLeaves) {
    MerkleTreeNode** nodes = (MerkleTreeNode**)malloc(numLeaves * sizeof(MerkleTreeNode*));
    for (size_t i = 0; i < numLeaves; i++) {
        nodes[i] = (MerkleTreeNode*)malloc(sizeof(MerkleTreeNode));
        strcpy(nodes[i] -> data, leaves[i]);
        CalculateSHA256(leaves[i], nodes[i] -> hash);
        nodes[i] -> left = NULL;
        nodes[i] ->right = NULL;
    }

    while (numLeaves>1) {
        size_t parentIndex = 0;
        for (size_t i = 0; i <numLeaves; i += 2) {
            MerkleTreeNode* left = nodes[i];
            MerkleTreeNode* right = (i + 1 < numLeaves) ? nodes[i + 1] : NULL;
            MerkleTreeNode* parent = (MerkleTreeNode*)malloc(sizeof(MerkleTreeNode));

            strcpy(parent ->data, left ->hash);
            if (right != NULL) {
                strcat(parent -> data, right -> hash);
            }

            CalculateSHA256(parent -> data, parent ->hash);
            parent -> left = left;
            parent ->right = right;

            nodes[parentIndex++] = parent;
        }

        numLeaves = parentIndex;
    }

    MerkleTree* tree = (MerkleTree*)malloc(sizeof(MerkleTree));
    tree -> root = nodes[0];

    free(nodes);
    return tree;
}

// 插入节点
void InsertNode(MerkleTreeNode* root, const char* data) {
    MerkleTreeNode* newNode = (MerkleTreeNode*)malloc(sizeof(MerkleTreeNode));
    strcpy(newNode ->data, data);
    CalculateSHA256(data, newNode -> hash);
    newNode ->left = NULL;
    newNode -> right = NULL;

    if (root -> left == NULL) {
        root -> left = newNode;
    }
    else if (root -> right == NULL) {
        root -> right = newNode;
    }
    else {
        MerkleTreeNode* sibling = (MerkleTreeNode*)malloc(sizeof(MerkleTreeNode));
        strcpy(sibling -> data, root ->right -> hash);
        sibling -> left = root ->right;
        sibling -> right = newNode;
        CalculateSHA256(sibling -> data, sibling -> hash);

        root -> right = sibling;
        CalculateSHA256(root -> left -> hash, root -> right -> hash);
    }
}

// 删除节点
void DeleteNode(MerkleTreeNode* root, const char* data) {
    if (root == NULL) {
        return;
    }

    if (root -> left != NULL && strcmp(root -> left -> data, data) == 0) {
        free(root ->left);
        root -> left = NULL;
    }
    else if (root -> right != NULL && strcmp(root -> right -> data, data) == 0) {
        free(root ->right);
        root -> right = NULL;
    }
    else {
        DeleteNode(root -> left, data);
        DeleteNode(root -> right, data);
    }
}

// 更新节点
void UpdateNode(MerkleTreeNode* node, const char* newData) {
    strcpy(node -> data, newData);
    CalculateSHA256(newData, node -> hash);

    if (node -> left != NULL) {
        char newHash[MAX_DATA_LENGTH * 2 + 1];
        strcpy(newHash, node -> left -> hash);
        if (node ->right != NULL) {
            strcat(newHash, node -> right -> hash);
        }
        CalculateSHA256(newHash, node -> hash);
    }
}

// 检索节点
MerkleTreeNode* RetrieveNode(MerkleTreeNode* root, const char* data) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root -> data, data) == 0) {
        return root;
    }

    MerkleTreeNode* leftResult = RetrieveNode(root -> left, data);
    if (leftResult != NULL) {
        return leftResult;
    }

    MerkleTreeNode* rightResult = RetrieveNode(root -> right, data);
    if (rightResult != NULL) {
        return rightResult;
    }

    return NULL;
}

// 销毁 Merkle Tree
void DestroyMerkleTree(MerkleTreeNode* node) {
    if (node == NULL) {
        return;
    }

    DestroyMerkleTree(node -> left);
    DestroyMerkleTree(node -> right);

    free(node);
}

int main() {

    char* leaves[] = { "abcd", "acdew", "yuhgdcd", "576vdsj","cdsieydjk","e8hcdjsk","scidsozcerz","12738dsj","jinjixu123","202100150107","jjiuhb887","ji9jwk8"};
    size_t numLeaves = sizeof(leaves) / sizeof(leaves[0]);

    MerkleTree* tree = CreateMerkleTree(leaves, numLeaves);
    printf("Merkle Tree Root Hash: %s\n", tree -> root -> hash);

    InsertNode(tree -> root, "NewLeaf");
    printf("Merkle Tree Root Hash after Insertion: %s\n", tree -> root -> hash);

    MerkleTreeNode* retrievedNode = RetrieveNode(tree -> root, "leaf3");
    if (retrievedNode != NULL) {
        printf("Leaf3 Hash: %s\n", retrievedNode -> hash);
    }
    else {
        printf("Leaf3 not found.\n");
    }

    DeleteNode(tree -> root, "Leaf2");
    printf("Merkle Tree Root Hash after Deletion: %s\n", tree -> root -> hash);

    UpdateNode(tree ->root, "UpdatedLeaf");
    printf("Merkle Tree Root Hash after Update: %s\n", tree -> root -> hash);

    DestroyMerkleTree(tree -> root);
    free(tree);

    return 0;
}
