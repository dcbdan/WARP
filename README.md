# WARP
Wavelets with adaptive recursive partitioning applied to image reconstruction (both 2D and 3D). R users can directly use the code for real data analysis. Another branch ports the code to Matlab.

# Instructions
- In R, make sure RcppArmadillo is installed: `install.packages("RcppArmadillo")`
- Clone the code to `/path/to/WARP`
- Create a directory to contain the build, such as `/path/to/bld`
- Install the library: `R CMD INSTALL -l /path/to/bld /path/to/WARP`.
- In R, load the library: `library(WARP, lib.loc="/path/to/bld")`

# 2D example

The following code is available in the file `demo.r`.
```
library("WARP", lib.loc="/path/to/bld")

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

plot_image = function(input)
  image(
    t(apply(input, 2, rev)),
    col = grey(seq(0, 1, length = 256)))

par(mfrow = c(2,2))
plot_image(obs_true)
plot_image(obs_raw)
plot_image(BMA_no_cs)
plot_image(BMA_cs)

mse(obs_true)
mse(obs_raw)
mse(BMA_no_cs)
mse(BMA_cs)

```
