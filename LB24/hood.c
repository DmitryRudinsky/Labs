//
// Created by Дима on 30.05.2024.
//

#include "hood.h"


void work_with_token(Token token, Operation_stack_handle operationStack, TreeStack_handle treeStack) {
    if (token.type == INT || token.type == COMBINED) {
        TreeNode *current_node = create_tree_node(token);
        treeStack_push(treeStack, current_node);
        return;
    }

    if (token.type == CLOSING_BRACKET) {
        while (!operationStack_is_empty(operationStack)) {
            Token last_token = operationStack_pop(operationStack);
            if (last_token.type == OPENING_BRACKET) {
                break;
            }
            TreeNode *poped_node = create_tree_node(last_token);
            create_tree_from_stack(poped_node, treeStack);
            treeStack_push(treeStack, poped_node);

        }
    }else if(token.type == LAST_SPACE){
        while (!operationStack_is_empty(operationStack)){
            Token last_token = operationStack_pop(operationStack);
            TreeNode *poped_node = create_tree_node(last_token);
            create_tree_from_stack(poped_node, treeStack);
            treeStack_push(treeStack, poped_node);

        }
    }
    else {
        while (!operationStack_is_empty(operationStack)) {
            Token last_token = get_last_token(operationStack);
            if (last_token.type == OPENING_BRACKET || last_token.type == NONE) {
                break;
            }
            if ((token.type == PLUS || token.type == MINUS) &&
                (last_token.type == PLUS || last_token.type == MINUS || last_token.type == MULTIPLICATION ||
                 last_token.type == DIVISION || last_token.type == RAISE_TO_POWER)) {
                TreeNode *poped_node = create_tree_node(last_token);
                operationStack_pop(operationStack);
                create_tree_from_stack(poped_node, treeStack);
                treeStack_push(treeStack, poped_node);
            } else if ((token.type == MULTIPLICATION || token.type == DIVISION) &&
                       (last_token.type == MULTIPLICATION || last_token.type == DIVISION ||
                        last_token.type == RAISE_TO_POWER)) {
                TreeNode *poped_node = create_tree_node(last_token);
                operationStack_pop(operationStack);
                create_tree_from_stack(poped_node, treeStack);
                treeStack_push(treeStack, poped_node);
            } else if (token.type == RAISE_TO_POWER && last_token.type == RAISE_TO_POWER) {
                TreeNode *poped_node = create_tree_node(last_token);
                operationStack_pop(operationStack);
                create_tree_from_stack(poped_node, treeStack);
                treeStack_push(treeStack, poped_node);
            } else {
                break;
            }
        }
        operationStack_push(operationStack, token);
    }
}


TreeNode * create_tree_from_stack(TreeNode *poped_node, TreeStack_handle treeStack){
    TreeNode *last_tree_node = get_last_treeNode(treeStack);
    TreeNode *penultimate = get_penultimate_treeNode(treeStack);
    Token_type last_tree_node_type = last_tree_node->token.type;
    Token_type penultimate_type = penultimate->token.type;
    if (is_int_or_comb(last_tree_node_type) && is_int_or_comb(penultimate_type)){
        poped_node->left = penultimate;
        poped_node->right = last_tree_node;
        treeStack_pop(treeStack);
        treeStack_pop(treeStack);
    } else if(!is_int_or_comb(last_tree_node_type) && is_int_or_comb(penultimate_type)){
        if(last_tree_node->left != NULL && last_tree_node->right != NULL){
            poped_node->left = penultimate;
            poped_node->right = last_tree_node;
            treeStack_pop(treeStack);
            treeStack_pop(treeStack);
        }
    }
    else if(is_int_or_comb(last_tree_node_type) && !is_int_or_comb(penultimate_type)){
        if(penultimate->left != NULL && penultimate->right != NULL){
            poped_node->left = penultimate;
            poped_node->right = last_tree_node;
            treeStack_pop(treeStack);
            treeStack_pop(treeStack);
        }
    }
    else if(!is_int_or_comb(last_tree_node_type) && !is_int_or_comb(penultimate_type)){
        if(last_tree_node->left != NULL && last_tree_node->right != NULL && penultimate->left != NULL && penultimate->right != NULL){
            poped_node->left = penultimate;
            poped_node->right = last_tree_node;
            treeStack_pop(treeStack);
            treeStack_pop(treeStack);
        }
    }
    return poped_node;
}