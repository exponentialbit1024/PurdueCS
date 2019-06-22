from nbc import *
from vanilla import *
from data import *
from matplotlib import pyplot as plt

if __name__ == "__main__":

    sizes = [1, 5, 10, 20, 25, 30, 40, 50, 60, 70, 80, 90, 99]
    losses = []
    nbc_losses = []
    maxIter = 2
    for size in sizes:
        X = load_data("yelp_cat.csv")
        x1, x2 = split_data(X, size)
        save_split(x1, x2)
        X = load_data("train-set.csv")
        Xt = load_data("test-set.csv")

        nbc = NBC(X.as_matrix(), Xt.as_matrix())
        nbc.train()
        nbcloss = nbc.predict_test()
        nbc_losses.append(nbcloss)
        print("nbc ZERO-ONE LOSS=" + str(nbcloss))

        y = X['goodForGroups'].as_matrix()
        yt = Xt['goodForGroups'].as_matrix()
        mergeDf = binarize(X, Xt)
        X, Xt = split_vector(mergeDf[0], mergeDf[1])
        nn = train(X, maxIter, y)
        loss = predict_batch(Xt, yt, nn)
        losses.append(loss)
        print("pcp ZERO-ONE LOSS=" + str(loss))
        print("")

    plt.plot(sizes, losses)
    plt.plot(sizes, nbc_losses)
    plt.xlabel("Training set size %")
    plt.ylabel("Zero one loss")
    plt.show()
