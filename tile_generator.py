import cv2



# Load image
img = cv2.imread('assets/map3.png')

n_rows = 6
n_cols = 10

# Draw a grid
for i in range(1, n_rows):
    cv2.line(img, (0, i * img.shape[0] // n_rows), (img.shape[1], i * img.shape[0] // n_rows), (0, 0, 0), 2)
for i in range(1, n_cols):
    cv2.line(img, (i * img.shape[1] // n_cols, 0), (i * img.shape[1] // n_cols, img.shape[0]), (0, 0, 0), 2)
    
# Print image
cv2.imshow('image', img)
cv2.waitKey(0)