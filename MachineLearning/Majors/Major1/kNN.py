from sklearn.base import BaseEstimator, ClassifierMixin
import numpy as np
import scipy


class kNN(BaseEstimator, ClassifierMixin):
    def __init__(self, n_neighbors: int = 3):
        self.n_neighbors = n_neighbors
        self.X_train = None
        self.y_train = None

    def fit(self, X, y):  # train
        # TODO: complete

        self.X_train = np.array(X)
        self.y_train = np.array(y)
        return

    def predict(self, X):
        # # Note: You can use self.n_neighbors here

        # TODO: compute the predicted labels (+1 or -1)
        distances = scipy.spatial.distance.cdist(X, self.X_train, metric='euclidean')

        idx = np.argpartition(distances, self.n_neighbors, axis=-1)[:, :self.n_neighbors]
        predictions = np.where(self.y_train[idx].mean(axis=1) >= 0, 1, -1)
        return predictions

