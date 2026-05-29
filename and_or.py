import numpy as np

# Fungsi aktivasi (step function)
def step_function(x):
    return 1 if x >= 0 else 0

# Training perceptron
def train_perceptron(X, y, learning_rate=0.1, epochs=20):

    # Inisialisasi bobot & bias
    weights = np.array([-0.3, 0.1], dtype=float)
    bias = 0.0

    converged = False

    for epoch in range(epochs):

        print(f"\n{'='*50}")
        print(f"Epoch {epoch+1}")
        print(f"{'='*50}")

        total_error = 0

        for i in range(len(X)):

            # hitung net
            linear_output = np.dot(X[i], weights) + bias

            # aktivasi
            y_pred = step_function(linear_output)

            # error
            error = y[i] - y_pred
            total_error += abs(error)

            # update bobot
            weights += learning_rate * error * X[i]
            bias += learning_rate * error

            print(f"Input: {X[i]} | "
                  f"Target: {y[i]} | "
                  f"Pred: {y_pred} | "
                  f"Error: {error} | "
                  f"w: {weights} | "
                  f"b: {bias:.2f}")

        print(f"\nTotal Error: {total_error}")
        print(f"Bobot akhir epoch: {weights}")
        print(f"Bias akhir epoch : {bias:.2f}")

        # cek konvergen
        if total_error == 0:
            print(f"\nKonvergen pada epoch {epoch+1}")
            converged = True
            break

    if not converged:
        print("\nBelum konvergen")

    return weights, bias


# Testing
def test_perceptron(X, weights, bias):

    print("\nHasil Testing:")
    print("-"*40)

    for x in X:

        net = np.dot(x, weights) + bias
        y_pred = step_function(net)

        print(f"Input: {x} | Net: {net:.2f} | Output: {y_pred}")


# =========================
# DATASET AND
# =========================

X_and = np.array([
    [0,0],
    [0,1],
    [1,0],
    [1,1]
])

y_and = np.array([0,0,0,1])

# =========================
# TRAINING
# =========================

print("=== TRAINING AND ===")

w_and, b_and = train_perceptron(
    X_and,
    y_and,
    learning_rate=0.1,
    epochs=20
)

# =========================
# TESTING
# =========================

test_perceptron(X_and, w_and, b_and)