import os
import cv2
import numpy as np

# (Keep your transformation functions here: negative_transform, log_transform, etc.)


def negative_transform(image: np.ndarray) -> np.ndarray:
  return 255 - image.copy()


def log_transform(image: np.ndarray) -> np.ndarray:
  img_float = image.astype(np.float32)
  c = 255.0 / np.log(1.0 + np.max(img_float))
  log_img = c * np.log(1.0 + img_float)
  return np.clip(log_img, 0, 255).astype(np.uint8)


def power_law_transform(image: np.ndarray, gamma: float = 1.5) -> np.ndarray:
  img_float = image.astype(np.float32) / 255.0
  gamma_img = np.power(img_float, gamma) * 255.0
  return np.clip(gamma_img, 0, 255).astype(np.uint8)


def contrast_stretching(image: np.ndarray) -> np.ndarray:
  r_min = np.min(image)
  r_max = np.max(image)
  if r_max == r_min:
    return image.copy()
  stretched = (image.astype(np.float32) - r_min) * (255.0 / (r_max - r_min))
  return np.clip(stretched, 0, 255).astype(np.uint8)


def thresholding(image: np.ndarray, thresh: int = 127) -> np.ndarray:
  return np.where(image > thresh, 255, 0).astype(np.uint8)


def histogram_equalization(image: np.ndarray) -> np.ndarray:
  hist = np.zeros(256, dtype=int)
  for row in image:
    for val in row:
      hist[val] += 1
  cdf = hist.cumsum()
  cdf_min = cdf[cdf > 0][0]
  total_pixels = image.shape[0] * image.shape[1]
  lut = np.zeros(256, dtype=np.uint8)
  for i in range(256):
    if total_pixels - cdf_min == 0:
      lut[i] = i
    else:
      val = ((cdf[i] - cdf_min) / (total_pixels - cdf_min)) * 255.0
      lut[i] = np.clip(round(val), 0, 255)
  return lut[image]


if __name__ == "__main__":
  # 1. Define the output folder name
  output_folder = "outputs"

  # 2. Create the folder automatically if it doesn't exist
  os.makedirs(output_folder, exist_ok=True)

  image = cv2.imread("photo.jpg")

  if image is None:
    print("Error: Could not load image. Check file path.")
  else:
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    resized_gray = cv2.resize(gray, (600, 450))

    # Apply transformations
    neg = negative_transform(resized_gray)
    log_img = log_transform(resized_gray)
    gamma_img = power_law_transform(resized_gray, gamma=2.0)
    stretched = contrast_stretching(resized_gray)
    thresh = thresholding(resized_gray, thresh=120)
    hist_eq = histogram_equalization(resized_gray)

    # 3. Save each image into the specified folder using os.path.join
    cv2.imwrite(os.path.join(output_folder, "negative.jpg"), neg)
    cv2.imwrite(os.path.join(output_folder, "log_transform.jpg"), log_img)
    cv2.imwrite(os.path.join(output_folder, "power_law.jpg"), gamma_img)
    cv2.imwrite(
        os.path.join(output_folder, "contrast_stretching.jpg"), stretched
    )
    cv2.imwrite(os.path.join(output_folder, "threshold.jpg"), thresh)
    cv2.imwrite(os.path.join(output_folder, "histogram_eq.jpg"), hist_eq)

    print(f"All images successfully saved inside the '{output_folder}' folder!")

    # Display results
    cv2.imshow("Original Grayscale", resized_gray)
    cv2.imshow("Negative / Inverse", neg)
    cv2.imshow("Log Transformation", log_img)
    cv2.imshow("Power Law (Gamma)", gamma_img)
    cv2.imshow("Contrast Stretching", stretched)
    cv2.imshow("Thresholding", thresh)
    cv2.imshow("Histogram Equalization", hist_eq)

    cv2.waitKey(0)
    cv2.destroyAllWindows()