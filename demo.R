library("WARP", lib.loc="/path/to/bld/")

lena <- as.matrix(read.csv("/path/to/WARP/lena_data.csv",header=FALSE))

obs_true <- lena / 255
obs_true <- obs_true
mse = function(x){ mean((obs_true - x)^2) }

sigma = 0.2
nr <- nrow(obs_true)
nc <- ncol(obs_true)
obs_raw <- obs_true + matrix(rnorm(nr*nc, sd = sigma), nrow = nr)
obs <- as.numeric(obs_raw)
dimension <- c(nr, nc)

hyper0 = hyper_default(obs, dimension)

BMA_no_cs = tree_fit(obs, dimension, hyper0, 0)
BMA_no_cs = matrix(BMA_no_cs, nrow = nr, ncol = nc)

step = 1
BMA_cs = tree_fit(obs, dimension, hyper0, step)
BMA_cs = matrix(BMA_cs, nrow = nr, ncol = nc)

par(mfrow = c(2,2))
image(obs_true)
image(obs_raw)
image(BMA_no_cs)
image(BMA_cs)

mse(obs_true)
mse(obs_raw)
mse(BMA_no_cs)
mse(BMA_cs)





