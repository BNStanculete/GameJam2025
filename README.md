# Way of working

To ensure we do not overwrite each other's changes, I propose the following way of working for the GameJam:
1. The `main` branch is protected - meaning code cannot be pushed directly onto it. It will have to be merged from your own branches.
2. The way you split work into branches is up to you, but when you want to merge into `main` create a new independent branch with your changes. During the review, only the dedicated branch will be updated.
3. Give commit messages meaningful descriptions so we know what we did xD
4. When creating a merge request (MR) make sure to:
   1. Add to `TODO.md` what still needs to be done (if applicable)
   2. List in the description of the merge request what you changed (i.e. stuff you added, bug fixes, etc.)
   3. Make sure that there are no compilation errors.
   4. Make sure that you pulled the latest changes and fixed any conflicts.
5. The MR has to be approved by the other 2 people (this ensures that everyone is up to speed with what's changed.)

## Git tutorial

To get your local copy of the project:

```
git clone https://github.com/BNStanculete/GameJam2025
```

To fetch existing branches:

```
git fetch --all
```

To create your own branch:

```
git branch [BRANCH_NAME]
```

To go between different branches (make sure that the branch has been created locally):

```
git checkout [BRANCH_NAME]
```

To pull changes from the remote server from a specific branch:

```
git pull origin [BRANCH_NAME]
```

Before pushing to the server run the command below, to put your changes ON TOP of the latest merged content. 

```
git rebase origin main
```

To commit your changes (i.e. save them locally); (make sure to type in the commit message):

```
git add . && git commit
```

To push your changes to your branch (make sure that the branch on Github is the same as your local one):

```
git push origin [BRANCH_NAME]
```

Merge requests are created from Github directly.

## Example workflow

Bogdan wants to start working on a new enemy. He has his local ```bogdan_dev``` branch where he keeps his local copy of the project. Bogdan works on his enemy locally until he's done. After that, he creates a new branch called ```bogdan_enemy1``` which has all his changes for the new enemy. He commits the changes on ```bogdan_enemy1``` and ensures they are the latest changes by running ```git rebase origin main```. After compiling, he pushes it to the Github using ```git push origin bogdan_enemy1```. From the Github website, he then creates a Merge Request for ```bogdan_enemy1``` (not ```bogdan_dev```). Until George and Andreea review his changes, Bogdan switches locally back to ```bogdan_dev``` and pulls the latest changes using ```git pull origin main```.