import os
Import("env")

print(">>> Current CLI targets", COMMAND_LINE_TARGETS)
print(">>> Current Build targets", BUILD_TARGETS)
# print(env.Dump())
# host = env.GetProjectOption("custom_ping_host")

def before_buildfs(source, target, env):
    print("\n>>>  before_buildfs: build-www")
    env.Execute("ruby shared/build-www.rb")

    print("\n>>> before_buildfs: copy assets")
    env.Execute("rsync --delete -av shared/assets/ data/assets/")

    print("\n>>> before_buildfs: gzip assets")
    env.Execute("find data/ -type f \( -name \*.css -o -name \*.js -o -name \*.html \) -exec gzip -f \"{}\" \;")

    print("\n>>> before_buildfs: total size")
    env.Execute("du -sh data")
    env.Execute("du -sh data/*")


env.AddPreAction("buildfs", before_buildfs)


def after_buildfs(source, target, env):
    print("\n>>> after_buildfs: unzip assets")
    # env.Execute("find data/ -type f -name *.gz -exec gunzip -f \"{}\" \;")

env.AddPostAction("buildfs", after_buildfs)
