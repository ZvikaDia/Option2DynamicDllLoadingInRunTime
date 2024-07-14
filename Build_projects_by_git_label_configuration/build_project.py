import re
import os
import json
import subprocess
from collections import defaultdict


def parse_sln_file(sln_path):
    projects = {}
    project_dependencies = defaultdict(set)

    with open(sln_path, 'r') as sln_file:
        content = sln_file.read()

        # Extract project information
        project_pattern = r'Project\("\{[^}]+\}"\)\s*=\s*"([^"]+)",\s*"([^"]+)",\s*"\{([^}]+)\}"'
        for match in re.finditer(project_pattern, content):
            name, path, guid = match.groups()
            projects[guid] = {'name': name, 'path': path, 'guid': guid}

        # Extract project dependencies
        dependency_pattern = r'ProjectSection\(ProjectDependencies\)\s*=\s*postProject([\s\S]*?)EndProjectSection'
        for match in re.finditer(dependency_pattern, content):
            deps_section = match.group(1)
            dep_lines = deps_section.strip().split('\n')
            for line in dep_lines:
                parts = line.strip().split(' = ')
                if len(parts) == 2:
                    dependent_guid, dependency_guid = parts
                    project_dependencies[dependent_guid].add(dependency_guid)

    return projects, project_dependencies


def topological_sort(projects, dependencies):
    sorted_projects = []
    visited = set()

    def visit(guid):
        if guid in visited:
            return
        visited.add(guid)
        for dep_guid in dependencies[guid]:
            visit(dep_guid)
        sorted_projects.append(guid)

    for guid in projects:
        visit(guid)

    return sorted_projects


def read_config_file(config_path):
    with open(config_path, 'r') as config_file:
        return json.load(config_file)


def checkout_and_build_project(project, git_label=None):
    project_path = os.path.dirname(project['path'])

    # Change to project directory
    os.chdir(project_path)

    if git_label:
        print(f"Checking out {git_label} for {project['name']}")
        subprocess.run(['git', 'checkout', git_label], check=True)
    else:
        print(f"Using current version for {project['name']}")

    # Build the project
    print(f"Building {project['name']}")
    # Replace the following line with your actual build command
    subprocess.run(['msbuild', project['path'], '/p:Configuration=Release'], check=True)


def main(sln_path, config_path):
    projects, dependencies = parse_sln_file(sln_path)
    sorted_guids = topological_sort(projects, dependencies)
    config = read_config_file(config_path)

    print("Projects in build order:")
    for guid in reversed(sorted_guids):
        project = projects[guid]
        project_name = project['name']
        print(f"- {project_name} ({project['path']})")

        git_label = config.get(project_name)
        try:
            checkout_and_build_project(project, git_label)
        except subprocess.CalledProcessError as e:
            print(f"Error building {project_name}: {e}")
            # Decide whether to continue or exit based on your requirements
            # For now, we'll continue with the next project
            continue

def main(sln_path):
    projects, dependencies = parse_sln_file(sln_path)
    sorted_guids = topological_sort(projects, dependencies)

    print("Projects in build order:")
    for guid in reversed(sorted_guids):
        print(f"- {projects[guid]['name']} ({projects[guid]['path']})")


if __name__ == "__main__":
    sln_path = r"D:\Projects\Option2DynamicDllLoadingInRunTime\Option2DynamicDllLoadingInRunTime.sln"  # Replace with your .sln file path
    config_path = r"D:\Projects\Option2DynamicDllLoadingInRunTime\Build_projects_by_git_label_configuration\labels.yml"  # Replace with your config file path
    main(sln_path, config_path)
    