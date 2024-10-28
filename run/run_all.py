import subprocess
import time
import atexit
import signal

processes = []


def run_command(command):
    try:
        process = subprocess.Popen(
            ["zsh", "-c", command],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        processes.append(process)
        return process
    except Exception as e:
        print("命令执行失败:", str(e))


def cleanup():
    for process in processes:
        try:
            process.send_signal(signal.SIGTERM)
            process.wait(timeout=5)
        except Exception as e:
            print("无法终止进程:", str(e))


atexit.register(cleanup)

if __name__ == "__main__":
    processes.append(
        run_command("cd ~/YOPO/flightrender/RPG_Flightmare && ./flightmare.x86_64")
    )
    processes.append(
        run_command("cd run && python test_yopo_ros.py --trial=1 --epoch=0 --iter=0")
    )
    processes.append(run_command("roslaunch so3_quadrotor_simulator simulator.launch"))
    processes.append(run_command("cd flightlib/build && ./flightros_node"))
    processes.append(run_command("cd flightlib/build && ./yopo_planner_node"))

    # 等待30秒后运行rviz命令
    time.sleep(30)
    processes.append(run_command("rviz -d yopo.rviz"))

    for process in processes:
        stdout, stderr = process.communicate()
        if process.returncode == 0:
            print("命令输出:", stdout.decode())
        else:
            print("命令执行失败:", stderr.decode())
