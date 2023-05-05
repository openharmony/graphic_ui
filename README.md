# UI<a name="EN-US_TOPIC_0000001123180295"></a>

-   [Introduction](#section11660541593)
-   [Directory Structure](#section161941989596)
-   [Constraints](#section119744591305)
-   [Compilation and Building](#section137768191623)
-   [Description](#section1312121216216)
    -   [Component Description](#section66002422015)
    -   [Usage](#section129654513264)

-   [Repositories Involved](#section1371113476307)

## Introduction<a name="section11660541593"></a>

The graphics UI module implements a system-level graphics engine.

This module provides the UIKit APIs for application development. You can use the APIs to add animations, manage layouts, transform images, process events, and operates on rich UI components.

The graphics UI directly calls the HAL API or uses the client provided by the Window Manager Service \(WMS\) to interact with the hardware to complete operations such as event response and image drawing.

**Figure  1**  Graphics subsystem architecture<a name="fig1358754417214"></a>  
![](figures/graphics-subsystem-architecture.png "graphics-subsystem-architecture")

## Directory Structure<a name="section161941989596"></a>

```
/foundation/arkui/ui_lite
├── frameworks                  # Framework code
│   ├── animator                # Animator module
│   ├── common                  # Common module
│   ├── components              # Components
│   ├── core                    # UI main processes (such as rendering and task management)
│   ├── default_resource
│   ├── dfx                     # Maintenance and test
│   ├── dock                    # Driver adaptation layer
│   │   └── ohos                # OHOS platform adaptation
│   ├── draw                    # Drawing logic
│   ├── engines                 # Drawing engines
│   ├── events                  # Events
│   ├── font                    # Fonts
│   ├── imgdecode               # Image management
│   ├── layout                  # Page layout
│   ├── themes                  # Theme management
│   ├── window                  # Window management adaptation layer
│   └── window_manager
│       └── dfb
├── interfaces                  # APIs
│   ├── innerkits               # APIs between modules
│   │   └── xxx                 # Sub-module APIs
│   └── kits                    # External APIs
│   │   └── xxx                 # Sub-module APIs
├── test                        # Test code
│   ├── framework
│   │   ├── include             # Header files for the test framework
│   │   └── src                 # Source code for the test framework
│   ├── uitest                  # Display effect test (The executable program is in foundation/window/window_manager_lite/test:sample_ui.)
│   │   └── test_xxx            # Specific UI effect test
│   └── unittest                # Unit testing
│       └── xxx                 # Unit testing for a specific UI component
└── tools                       # Test and simulation tools (simulator projects and resource files)
    └── qt                      # Qt project
```

## Constraints<a name="section119744591305"></a>

Platform Constraints

-   The Windows platform supports only Qt and OHOS IDE.
-   For the support of other platforms, see the  **graphic**  tag in  **vendor/hisilicon/\[product\_name\]/config.json**. If the  **graphic**  tag does not exist, it indicates that the product does not have the graphics subsystem.

## Compilation and Building<a name="section137768191623"></a>

```
# Generate the libui.so file in the out directory of the product folder through GN compilation.
hb build -T //foundation/arkui/ui_lite:ui_lite -f  #build libui.so
hb build -T //foundation/indow/window_manager_lite/test:sample_ui -f # build UI demo
hb build -T //foundation/arkui/ui_lite/test/unittest:arkui_ui_lite_test -f # build TDD testcases

# To compile the Qt library, see the Qt simulator project at arkui/ui_lite/tools/qt/simulator/simulator.pro.
```

## Description<a name="section1312121216216"></a>

### Component Description<a name="section66002422015"></a>

Components are classified into basic components and container components.

-   Basic components: Implement only a single function, such as  **Text**,  **Button**,  **Image**, and  **List**.
-   Container components: Hold and combine child components to implement complex functions.

**Figure  2**  Graphics subsystem components<a name="fig1594213196218"></a>  
![](figures/graphics-subsystem-components.png "graphics-subsystem-components")

### Usage<a name="section129654513264"></a>

For details about how to use components and APIs of graphics, see the examples provided in  **foundation/arkui/ui_lite/test/uitest**.

-   The Qt project can be debugged in the Windows environment. [User Guide](https://gitee.com/openharmony/arkui_ui_lite/wikis/%E5%BF%AB%E9%80%9F%E5%8A%A0%E5%85%A5/%E5%8A%A0%E5%85%A5%E6%8C%87%E5%BC%95)

    Project file path:

    ```
    arkui/ui_lite/tools/qt/simulator/simulator.pro
    ```

-   For other debugging environments, you can run  **foundation/window/window_manager_lite/test:sample\_ui**.

    After the building is successful, the executable program  **out/\[product\_name\]/dev\_tools/bin/sample\_ui**  is obtained. You can run the program in an environment to view the display effect of a specific component.


## Repositories Involved<a name="section1371113476307"></a>

[Graphic subsystem](https://gitee.com/openharmony/docs/blob/master/en/readme/graphics.md)

[graphic_wms](https://gitee.com/openharmony/graphic_wms/blob/master/README.md)

[graphic_surface](https://gitee.com/openharmony/graphic_surface/blob/master/README.md)

**graphic_ui**

[graphic_utils](https://gitee.com/openharmony/graphic_utils/blob/master/README.md)