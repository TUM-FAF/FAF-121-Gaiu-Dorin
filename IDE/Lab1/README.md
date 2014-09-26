<h1>Laboratory Work 1</h1>
<h4>Command Line Interface; CLI Editors; Setting Server Environment; Version Control Systems</h4>

<h3>Executed Tasks</h3>
<h4>Mandatory Tasks:</h4>
- Connect to a remote server via SSH
<p>To complete this task, i used Mac OS X Terminal and the comand: <i>ssh UserName@IP</i></p>
- Initialize a repository on server
<p> I created a folder by typing: <i>mkdir folder_name </i></p>
<p> Then i changed the current directory to the create one by writing :
<i>cd folder_name</i></p>
<p><i>git init </i> initialized the empty repository in that folder.</p>
- Create a file in repository folder, write in your name, save it and commit it
<p><i>touch fileName.txt</i> - create a file</p>
<p><i>vim fileName.txt</i> - opens the file in vim</p>
<p><i>i</i> - insert mode</p>
<p><i>Esc key</i> - exit from insert mode</p>
<p><i>:wq</i> - save the file and exit</p>
<p><i> git add fileName.txt</i> - track the file</p>
<p><i>git commit -m "some text"</i> - commit </p>

<h4> Tasks With points:</h4>
- Connect to server using public key (1 pt)
<p> To connect to a server using a public key we have to generate a RSA key pair by writing: <i>ssh-keygen -t rsa</i></p>
<p> In order to append public key to <i>authorized_keys</i> we run: <i> cat ~/.ssh/id_rsa.pub | ssh user@ip "cat - >> ~/.ssh/authorized_keys"</i>, which links contents of id_rsa.pub into <i>authorized_keys</i> on server</p>
- Create 2 more branches with at least one unique committed file per branch (1 pt)
<p> To create a new branch we run: <i>git branch branch_name</i> , then we use <i>git checkout branch_name</i> to switch to it.<p>
<p> We create files using <i>touch</i> command then we commit.</p>
- Reset a branch to previous commit, reset a branch to some specific commit (1 pt)
<p><i>git reset --hard head^</i></p>
<p>It's recomended to use git status before this change.</p>
- Restore a reset branch back to its previous state (1 pt)
<p> To reset branch to a previous state we type: <i> git reset --hard some_commit</i> </p>
