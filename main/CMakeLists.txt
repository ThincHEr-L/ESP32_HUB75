idf_component_register(
                    SRCS "user_Uart1_task.c" 
                    SRCS "main.c"
                    SRCS "user_Plight_task.c"
                    SRCS "user_hub75_task.c"
                    SRCS "hub75e/HUB75ELib.c" "hub75e/HUB75E_Hal.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES hub75
                    PRIV_REQUIRES driver)
                    