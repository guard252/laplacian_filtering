# laplacian_filtering

## General information
This is an implementation of edge-aware image processing using laplacian pyramid, explained in depth in this article:
https://people.csail.mit.edu/sparis/publi/2011/siggraph/Paris_11_Local_Laplacian_Filters.pdf

All the computations are done on the CPU-side, so it is likely going to take a while to process big images. I have also made a GPU implementation, which is now under NDA, but if you want, you can contact me on Telegram (@sadiuk) or Discord (@sadiuk#7570) and I'll give you some hints on how to implement it properly.

## Clone and build

To clone the repo, just enter *git clone https://github.com/guard252/laplacian_filtering* into your git bash (no submodules required).
The app is written and tested on Ubuntu 18.04 with gcc compiler, so if you're using different environmet, you might have some troubles.

# Results

The filtering depends on three parameters - alpha, beta and sigma. 
Aplha is responsible for details enhancement/reduction, beta is the tone-mapping input parameter and the sigma is the parameter that defines at what level the features should be considered details or edges.

## Details Manipulation 


### Input image:

![Input image 1](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/input/flower.png)


### Sigma = 0.2, alpha = 0.5, beta = 1:

![Output image 1](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/detail_manipulation/images/flower_rgb_lin_s0.2_a0.5_b1.png)


### Sigma = 0.4, alpha = 0.25, beta = 1:

![Outpum image 2](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/detail_manipulation/images/flower_rgb_lin_s0.4_a0.25_b1.png) 


### Sigma = 0.2, alpha = 4, beta = 1:

![Output image 3](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/detail_manipulation/images/flower_rgb_lin_s0.2_a4_b1.png)

## Tone mapping (Sigma is good to be fixed at log(2.5))


### Input image:

![Input Image 3](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/input_HDR/HancockKitchenInside_small.png)


### Alpha = 1, beta = 0.6

![Output Image 4](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/tone_mapping/images/HancockKitchenInside_small_lum_log_s2.5_a1_b0.6.png)


### Alpha = 1, beta = 0.3

![Output Image 5](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/tone_mapping/images/HancockKitchenInside_small_lum_log_s2.5_a1_b0.3.png)


### Alpha = 1, beta = 0

![Output Image 6](https://people.csail.mit.edu/sparis/publi/2011/siggraph/additional_results/tone_mapping/images/HancockKitchenInside_small_lum_log_s2.5_a1_b0.png)


# That's it
If the code helped you in any way, fell free to star the repo :)

## Contacts

Telegram: @sadiuk

Discord: @sadiuk#7570

Email: danylotv43@gmail.com
