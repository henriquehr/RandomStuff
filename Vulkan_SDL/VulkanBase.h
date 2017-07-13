#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif // WIN32

#include <windows.h>
#include <string>
#include <vector>

#include <vulkan\vulkan.h>

#include "VulkanDebug.h"
#include "VulkanInitializers.hpp"
#include "VulkanDevice.hpp"
#include "VulkanSwapChain.hpp"


class VulkanBase
{
public:
	struct {
		// Swap chain image presentation
		VkSemaphore presentComplete;
		// Command buffer submission and execution
		VkSemaphore renderComplete;
		// Text overlay submission and execution
		VkSemaphore textOverlayComplete;
	} semaphores;

	VulkanBase();
	virtual ~VulkanBase();
	void initVulkan();
	VkResult VulkanBase::createInstance();
	VkBool32 VulkanBase::getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat *depthFormat);
	HWND VulkanBase::setupWindow(HINSTANCE hinstance, WNDPROC wndproc);
	void VulkanBase::handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	std::string name = "vulkanExample";
	bool validation = false;
	const std::vector<char*> validationLayer = { "VK_LAYER_LUNARG_standard_validation" };
	// Vulkan instance
	VkInstance instance;
	// Physical device (GPU)
	VkPhysicalDevice physicalDevice;
	// Stores physical device properties
	VkPhysicalDeviceProperties deviceProperties;
	// Stores the features available on the selected physical device
	VkPhysicalDeviceFeatures deviceFeatures;
	// Stores all available memory properties for the physical device
	VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
	/** @brief Encapsulated physical and logical vulkan device */
	vks::VulkanDevice *vulkanDevice;
	/**@note By default no phyiscal device features are enabled*/
	VkPhysicalDeviceFeatures enabledFeatures{};
	/** @brief Set of device extensions to be enabled for this example (must be set in the derived constructor) */
	std::vector<const char*> enabledExtensions;
	VkDevice device;
	// Handle to the device graphics queue that command buffers are submitted to
	VkQueue queue;
	// Depth buffer format (selected during Vulkan initialization)
	VkFormat depthFormat;
	// Wraps the swap chain to present images (framebuffers) to the windowing system
	VulkanSwapChain swapChain;
	// Contains command buffers and semaphores to be presented to the queue
	VkSubmitInfo submitInfo;
	/** @brief Pipeline stages used to wait at for graphics queue submissions */
	VkPipelineStageFlags submitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	HWND window;
	HINSTANCE windowInstance;

	uint32_t width = 1280;
	uint32_t height = 720;


};

