'''
Descripttion: 
Author: ssw
Date: 2022-04-02 15:59:33
LastEditors: ssw
LastEditTime: 2022-04-02 20:42:20
'''
from distutils.log import error
import numpy as np


def LUPSolve(L, U, pi, b):
    n = L.shape[0]
    y = np.zeros((n, 1))
    x = np.zeros((n, 1))
    for i in range(n):
        y[i] = b[pi[i]] - np.dot(L[i], y)
    for i in range(n-1, -1, -1):
        x[i] = (y[i]-np.dot(U[i], x))/U[i, i]
    return x


def LUDecomposition(A):
    n = A.shape[0]
    L, U = np.eye(n), np.zeros((n, n))
    for k in range(n):
        U[k, k] = A[k, k]
        for i in range(k+1, n):
            L[i, k] = A[i, k]/U[k, k]
            U[k, i] = A[k, i]
        for i in range(k + 1, n):
            for j in range(k+1, n):
                A[i, j] -= L[i, k]*U[k, j]
    return L, U


def LUPDecomposition(A):
    n = A.shape[0]
    pi = np.zeros((n, 1))
    for i in range(n):
        pi[i] = i
    for k in range(n):
        p = 0
        for i in range(k, n):
            if np.abs(A[i, k]) > p:
                p = np.abs(A[i, k])
                k_ = i
        if p == 0:
            error("singular matrix")
        pi[k], pi[k_] = pi[k_], pi[k]
        A[[k, k_], :] = A[[k_, k], :]
        for i in range(k+1, n):
            A[i, k] /= A[k, k]
            for j in range(k+1, n):
                A[i, j] -= A[i, k]*A[k, j]
    return A


L = np.array([[1, 0, 0], [0.2, 1, 0], [0.6, 0.5, 1]])
U = np.array([[5, 6, 3], [0, 0.8, -0.6], [0, 0, 2.5]])
b = np.array([3, 7, 8])
pi = np.array([2, 0, 1])
# print(LUPSolve(L, U, pi, b))

A = np.array([[2, 3, 1, 5],
              [6, 13, 5, 19],
              [2, 19, 10, 23],
              [4, 10, 11, 31]])

# print(LUDecomposition(A))

AA = np.array([[2, 0, 2, 0.6],
               [3, 3, 4, -2],
               [5, 5, 4, 2],
               [-1, -2, 3.4, -1]])

print(LUPDecomposition(AA))
