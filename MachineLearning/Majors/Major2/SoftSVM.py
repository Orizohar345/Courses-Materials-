from sklearn.base import BaseEstimator, ClassifierMixin
import numpy as np


# Part 3 - Soft SVM
class SoftSVM(BaseEstimator, ClassifierMixin):
    """
    Custom C-Support Vector Classification.
    """

    def __init__(self, C: float, lr: float = 1e-5, batch_size=32):
        """
        Initialize an instance of this class.
        ** Do not edit this method **

        :param C: inverse strength of regularization. Must be strictly positive.
        :param lr: the SGD learning rate (step size)
        """
        self.C = C
        self.lr = lr
        self.batch_size = batch_size
        self.w = None
        self.b = 0.0

    # Initialize a random weight vector
    def init_solution(self, n_features: int):
        """
        Randomize an initial solution (weight vector)
        ** Do not edit this method **

        :param n_features:
        """
        self.w = np.random.randn(n_features)
        self.b = 0.0

    @staticmethod
    def loss(w, b: float, C: float, X, y):
        """
        Compute the SVM objective loss.

        :param w: weight vector for linear classification; array of shape (n_features,)
        :param b: bias scalar for linear classification
        :param C: inverse strength of regularization. Must be strictly positive.
        :param X: samples for loss computation; array of shape (n_samples, n_features)
        :param y: targets for loss computation; array of shape (n_samples,)
        :return: the Soft SVM objective loss (float scalar)
        """
        margins = (X.dot(w) + b).reshape(-1, 1)  # (X^T)W+b
        hinge_inputs = np.multiply(margins, y.reshape(-1, 1))  # z=y(W^Tx+b)
        ones_vec = np.ones(len(hinge_inputs))  # 0
        zeros_vec = np.zeros(len(hinge_inputs))  # 1
        loss_inputs = np.subtract(ones_vec.reshape(-1, 1), hinge_inputs.reshape(-1, 1))  # 1-z
        loss_vec = np.maximum(zeros_vec.reshape(-1, 1, ), loss_inputs)  # max(1-z,0)
        loss_sum = np.sum(loss_vec)  # sum of max(1-z,0)

        norm = np.linalg.norm(w)

        # TODO: complete the loss calculation
        loss = norm ** 2 + C * loss_sum  # C*loss_sum + ||w||^2

        return loss

    @staticmethod
    def subgradient(w, b: float, C: float, X, y):
        """
        Compute the (analytical) SVM objective sub-gradient.

        :param w: weight vector for linear classification; array of shape (n_features,)
        :param b: bias scalar for linear classification
        :param C: inverse strength of regularization. Must be strictly positive.
        :param X: samples for loss computation; array of shape (n_samples, n_features)
        :param y: targets for loss computation; array of shape (n_samples,)
        :return: a tuple with (the gradient of the weights, the gradient of the bias)
        """
        # TODO: calculate the analytical sub-gradient of soft-SVM w.r.t w and b
        margins = (X.dot(w) + b).reshape(-1, 1)  # W^Tx+b
        hinge_inputs = np.multiply(margins, y.reshape(-1, 1))  # z=y(W^Tx+b)
        ones_vec = np.ones(len(hinge_inputs)).reshape(-1, 1)  # 1
        f_input = np.subtract(hinge_inputs, ones_vec)  # z-1
        f_output = np.where(np.sign(f_input) > 0, 0, -1)
        signed_y = np.multiply(f_output, y.reshape(-1, 1))  # y*f(z)

        sum_signed_y = np.sum(signed_y)  # sum i=1 to m for y*f(z)

        g_b = np.multiply(sum_signed_y, C)  # return C*sum

        to_sum = np.multiply(X, signed_y)  # y*f(z)*x
        sum = np.sum(to_sum, axis=0)  # sum i=1 to m of y*f(z)*x

        g_w = np.multiply(sum, C) + 2 * w  # C*(sum i=1 to m of y*f(z)*x) +2w

        return g_w, g_b

    def fit_with_logs(self, X, y, max_iter: int = 2000, keep_losses: bool = True):
        """
        Fit the model according to the given training data.

        :param X: training samples; array of shape (n_samples, n_features)
        :param y: training targets (+1 and -1); array of shape (n_samples,)
        :param max_iter: number of SGD iterations
        :param keep_losses:
        :return: the training losses and accuracies during training
        """
        # Initialize learned parameters
        self.init_solution(X.shape[1])

        losses = []
        accuracies = []

        if keep_losses:
            losses.append(self.loss(self.w, self.b, self.C, X, y))
            accuracies.append(self.score(X, y))

        permutation = np.random.permutation(len(y))
        X = X[permutation, :]
        y = y[permutation]

        # Iterate over batches
        for iter in range(0, max_iter):
            start_idx = (iter * self.batch_size) % X.shape[0]
            end_idx = min(X.shape[0], start_idx + self.batch_size)
            batch_X = X[start_idx:end_idx, :]
            batch_y = y[start_idx:end_idx]

            # TODO: Compute the (sub)gradient of the current *batch*
            g_w, g_b = self.subgradient(self.w, self.b, self.C, batch_X, batch_y)

            # Perform a (sub)gradient step
            # TODO: update the learned parameters correctly
            self.w = self.w - self.lr * g_w
            self.b = self.b - self.lr * g_b

            if keep_losses:
                losses.append(self.loss(self.w, self.b, self.C, X, y))
                accuracies.append(self.score(X, y))

        return losses, accuracies

    def fit(self, X, y, max_iter: int = 2000):
        """
        Fit the model according to the given training data.
        ** Do not edit this method **

        :param X: training samples; array of shape (n_samples, n_features)
        :param y: training targets (+1 and -1); array of shape (n_samples,)
        :param max_iter: number of SGD iterations
        """
        self.fit_with_logs(X, y, max_iter=max_iter, keep_losses=False)

        return self

    def predict(self, X):
        """
        Perform classification on samples in X.

        :param X: samples for prediction; array of shape (n_samples, n_features)
        :return: Predicted class labels for samples in X; array of shape (n_samples,)
                 NOTE: the labels must be either +1 or -1
        """
        # TODO: compute the predicted labels (+1 or -1)
        y = np.dot(X, self.w) + self.b  # X*w +b
        y = np.sign(y)
        y_pred = y

        return y_pred
