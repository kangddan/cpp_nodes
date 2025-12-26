from maya import cmds

def main():
    loc1 = cmds.spaceLocator()[0]
    loc2 = cmds.spaceLocator()[0]
    
    jointCount = 100
    joints = [cmds.createNode('joint') for i in range(jointCount)]
    cmds.setAttr(f'{loc1}.tx', -4)
    cmds.setAttr(f'{loc2}.tx', 4)
    
    node = cmds.createNode('catenarySolver')
    
    cmds.connectAttr(f'{loc1}.t', f'{node}.input1')
    cmds.connectAttr(f'{loc2}.t', f'{node}.input2')
    cmds.setAttr(f'{node}.itemCount', jointCount)
    
    for index, joint in enumerate(joints):
        cmds.connectAttr(f'{node}.outputs[{index}]', f'{joint}.t')
        
if __name__ == '__main__':
    main()